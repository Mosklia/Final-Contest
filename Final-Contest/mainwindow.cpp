#include <QDebug>
#include "mainwindow.h"
#include "table.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , data_file(nullptr)
    , open_file_diag(new open_file_dialog(this))
    , save_file_diag(new save_file_dialog(this))
    , central(new QWidget(this))
    , main_layout(new QGridLayout(central))
    , tool_bar(new QToolBar(this))
    , load_file(new QAction("Load", this))
    , save_file(new QAction("Save", this))
    , save_as(new QAction("Save as", this))
    , detail_button(new QPushButton("Detail..", central))
    , main_model(new QStandardItemModel(this))
    , main_view(new QTableView(this))
    , trip_dia(new trip_dialog(this))
    , delegate_main(new blank_delegate(this))
//    , ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
    initialize_attributes();
    initialize_ui();
    initialize_connections();
}

MainWindow::~MainWindow()
{
//    delete ui;
    delete main_view;
    delete main_model;
    delete detail_button;
    delete tool_bar;
    delete save_as;
    delete save_file;
    delete load_file;
    delete main_layout;
    delete central;
    delete save_file_diag;
    delete open_file_diag;
    delete data_file;
}

void MainWindow::initialize_ui()
{
    addToolBar(tool_bar);
    resize(618, 420);

//    main_layout->insertWidget(1, detail_button);
//    main_layout->addWidget(tool_bar);
    setCentralWidget(central);

//    setLayout(main_layout);
    statusBar();
}

void MainWindow::initialize_attributes()
{
    load_file->setStatusTip("Load data from a file.");
    save_file->setStatusTip("Save data to current file.");
    save_as->setStatusTip("Save data to another file.");

    tool_bar->addAction(load_file);
    tool_bar->addAction(save_file);
    tool_bar->addAction(save_as);

    main_view->setSelectionMode(QAbstractItemView::SingleSelection);
    main_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    main_view->setModel(main_model);
    main_view->setItemDelegate(delegate_main);
//    main_view->set

    main_layout->addWidget(main_view, 0, 0, 1, 3);
    main_layout->addWidget(detail_button, 1, 1, Qt::AlignCenter);
    central->setLayout(main_layout);
    main_model->setColumnCount(6);
    main_model->setHorizontalHeaderLabels(QStringList({
        "No.",
        "Destination",
        "Departure date",
        "Departure time",
        "Capacity",
        "Seats available"
                                                      }));
}

void MainWindow::initialize_connections()
{
    connect(open_file_diag, &open_file_dialog::fileSelected,
            this, &MainWindow::on_open_file);
    connect(save_file_diag, &save_file_dialog::fileSelected,
            this, &MainWindow::on_save_file);

    connect(this, &MainWindow::readfile_opened,
            &main_table, &table::read_from);
    connect(this, &MainWindow::readfile_opened,
            this, &MainWindow::reload_model);
    connect(this, &MainWindow::writefile_opened,
            &main_table, &table::save_to);

    connect(load_file, &QAction::triggered,
            this, &MainWindow::on_loadfile_clicked);
    connect(save_file, &QAction::triggered,
            this, &MainWindow::on_savefile_clicked);
    connect(save_as, &QAction::triggered,
            this, &MainWindow::on_saveas_clicked);

    connect(delegate_main, &blank_delegate::created_blank_delegate,
            this, &MainWindow::show_detail);
    connect(detail_button, &QPushButton::clicked,
            this, &MainWindow::on_detail_clicked);

    connect(this, &MainWindow::iconSizeChanged,
            main_view, &QTableView::resizeColumnsToContents);
}

void MainWindow::on_open_file(const QString &file)
{
    if (data_file != nullptr && data_file->isOpen())
    {
        data_file->close();
    }
    delete data_file;

    data_file = new QFile(file);

    if (data_file->open(QIODevice::ReadOnly))
    {
        emit readfile_opened(*data_file);
    }
    else
    {
        emit file_open_failed(file);
    }
}

void MainWindow::on_save_file(const QString &file)
{
    if (data_file != nullptr && data_file->isOpen())
    {
        data_file->close();
    }
    delete data_file;

    data_file = new QFile(file);

    if (data_file->open(QIODevice::WriteOnly))
    {
        emit writefile_opened(*data_file);
    }
    else
    {
        emit file_open_failed(file);
    }
}

void MainWindow::on_loadfile_clicked()
{
    open_file_diag->exec();
}

void MainWindow::on_savefile_clicked()
{
    QString filename = data_file->fileName();
    on_save_file(filename);
}

void MainWindow::on_saveas_clicked()
{
    save_file_diag->exec();
}

void MainWindow::reload_model()
{
    main_model->clear();

    main_model->setColumnCount(6);
    main_model->setHorizontalHeaderLabels(QStringList({
        "No.",
        "Destination",
        "Departure date",
        "Departure time",
        "Capacity",
        "Seats available"
                                                      }));

    for (const auto &x : main_table.get_all_trips())
    {
        main_model->appendRow(QList<QStandardItem*>({
            new QStandardItem(x.get_id()),
            new QStandardItem(x.get_destination().replace('^', ' ')),
            new QStandardItem(x.get_departure_date().toString("yyyy-MM-dd")),
            new QStandardItem(x.get_departure_time().toString("HH:mm:ss")),
            new QStandardItem(QString::number(x.get_capacity())),
            new QStandardItem(QString::number(x.query_avaliable()))
                                                    }));

        if (x.get_departure_date() < QDate::currentDate() ||
            x.get_departure_date() >= QDate::currentDate().addDays(3))
        {
            main_view->setRowHidden(main_model->rowCount() - 1, true);
//            qDebug() << "Hidden: " << main_view->currentIndex().row() << '\n';
        }
    }
}

void MainWindow::show_detail(const QModelIndex &index)
{
    if (index.model() == main_model)
    {
        trip_dia->execute(main_table.get_trip(index.row()));
        reload_model();
    }
}

void MainWindow::on_detail_clicked()
{
    trip_dia->execute(main_table.get_trip(main_view->currentIndex().row()));
}
