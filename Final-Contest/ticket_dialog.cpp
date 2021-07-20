#include "ticket_dialog.h"

ticket_dialog::ticket_dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("ORDER!");
}

refund_dialog::refund_dialog(QWidget *parent)
    : QDialog(parent)
    , diag_layout(new QGridLayout(this))
    , bt_accept(new QPushButton("Confirm", this))
    , bt_refuse(new QPushButton("Cancel", this))
    , str(new QTextEdit("Confirm to refund?", this))
{
    setWindowTitle("Refund");
    setFixedSize(200, 125);

    connect(bt_accept, &QPushButton::clicked,
            this, &refund_dialog::accept);
    connect(bt_refuse, &QPushButton::clicked,
            this, &refund_dialog::reject);

    str->setReadOnly(true);
    str->setAcceptRichText(false);

    diag_layout->addWidget(str, 0, 0, 1, 2, Qt::AlignCenter);
    diag_layout->addWidget(bt_accept, 1, 0, Qt::AlignCenter);
    diag_layout->addWidget(bt_refuse, 1, 1, Qt::AlignCenter);

    setLayout(diag_layout);
}
