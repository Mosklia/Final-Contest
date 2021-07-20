#include "trip_dialog.h"

trip_dialog::trip_dialog(QWidget *parent)
    : QDialog(parent)
    , diag_layout(new QVBoxLayout(this))
    , change_button(new QPushButton(this))
    , order_diag(new ticket_dialog(this))
    , refund_diag(new refund_dialog(this))
    , model(new QStandardItemModel(this))
    , view(new QTableView(this))
    , delegate(new blank_delegate(this))
{
    setFixedSize(400, 300);
    model->setColumnCount(3);
    model->setHorizontalHeaderLabels(QStringList({"Avaliable", "Name", "ID No."}));
    view->setModel(model);
    view->setItemDelegate(delegate);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);

    change_button->setFixedSize(100, 40);
    diag_layout->addWidget(view);
    diag_layout->addWidget(change_button, Qt::AlignCenter);

    connect(change_button, &QPushButton::clicked,
            this, &trip_dialog::on_button_click);
    connect(delegate, &blank_delegate::created_blank_delegate,
            this, &trip_dialog::on_button_click);
    connect(this, &trip_dialog::order_requested,
            order_diag, &ticket_dialog::exec);
    connect(this, &trip_dialog::refund_requested,
            refund_diag, &refund_dialog::exec);
    connect(view, &QTableView::clicked,
            this, &trip_dialog::selection_changed);
    connect(this, &trip_dialog::refund_requested,
            this, &trip_dialog::process_refund);
}

void trip_dialog::execute(trip &source)
{
    data = &source;
    reload_model();

    exec();
}

void trip_dialog::selection_changed()
{
    int seat_id = view->currentIndex().row();
    if (data->get_seat(seat_id).avaliable)
    {
        change_button->setText("Order");
    }
    else
    {
        change_button->setText("Refund");
    }
}

void trip_dialog::reload_model()
{
    model->clear();

    model->setColumnCount(3);
    model->setHorizontalHeaderLabels(QStringList({"Avaliable", "Name", "ID No."}));

    for (const auto &x : data->get_all_seats())
    {
        model->appendRow(QList<QStandardItem*>({
            new QStandardItem(x.avaliable ? "true" : "false"),
            new QStandardItem(x.owner.get_name().replace('^', ' ')),
            new QStandardItem(x.owner.get_pid())
                                               }));
    }
}

void trip_dialog::on_button_click()
{
    int seat_id = view->currentIndex().row();
    if (data->get_seat(seat_id).avaliable)
    {
        emit order_requested();
    }
    else
    {
        emit refund_requested();
    }
}

trip_dialog::~trip_dialog()
{
    delete delegate;
    delete view;
    delete model;
    delete refund_diag;
    delete order_diag;
    delete change_button;
    delete diag_layout;
}

void trip_dialog::process_refund()
{
    int seat_id = view->currentIndex().row();
    if (refund_diag->result() == QDialog::Accepted)
    {
        data->erase_order(seat_id);
        reload_model();
    }
}
