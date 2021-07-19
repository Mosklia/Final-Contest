#include "mainwindow.h"
#include "table.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , data_file(nullptr)
    , open_file_diag(new open_file_dialog(this))
    , save_file_diag(new save_file_dialog(this))
    , load_file(new QAction("Load", this))
    , save_file(new QAction("Save", this))
    , save_as(new QAction("Save as", this))
    , tool_bar(new QToolBar(this))
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
    delete save_as;
    delete save_file;
    delete load_file;
    delete save_file_diag;
    delete open_file_diag;
    delete data_file;
}

void MainWindow::initialize_ui()
{
    addToolBar(tool_bar);
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
}

void MainWindow::initialize_connections()
{
    connect(open_file_diag, &open_file_dialog::fileSelected,
            this, &MainWindow::on_open_file);
    connect(save_file_diag, &save_file_dialog::fileSelected,
            this, &MainWindow::on_save_file);

    connect(this, &MainWindow::readfile_opened,
            &main_table, &table::read_from);
    connect(this, &MainWindow::writefile_opened,
            &main_table, &table::save_to);

    connect(load_file, &QAction::triggered,
            this, &MainWindow::on_loadfile_clicked);
    connect(save_file, &QAction::triggered,
            this, &MainWindow::on_savefile_clicked);
    connect(save_as, &QAction::triggered,
            this, &MainWindow::on_saveas_clicked);
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
