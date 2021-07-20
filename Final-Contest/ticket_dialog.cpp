#include "ticket_dialog.h"

ticket_dialog::ticket_dialog(QWidget *parent)
    : QDialog(parent)
    , diag_layout(new QGridLayout(this))
    , bt_accept(new QPushButton("Confirm", this))
    , bt_refuse(new QPushButton("Cancel", this))
    , label_name(new QLabel("Name:", this))
    , label_idnum(new QLabel("ID No.:", this))
    , entry_name(new QTextEdit(this))
    , entry_idnum(new QTextEdit(this))
{
    setWindowTitle("Order ticket");
    setFixedSize(300, 120);

    connect(bt_accept, &QPushButton::clicked,
            this, &refund_dialog::accept);
    connect(bt_refuse, &QPushButton::clicked,
            this, &refund_dialog::reject);

    diag_layout->addWidget(label_name, 0, 0, Qt::AlignRight);
    diag_layout->addWidget(label_idnum, 1, 0, Qt::AlignRight);
    diag_layout->addWidget(entry_name, 0, 1, 1, 2, Qt::AlignLeft);
    diag_layout->addWidget(entry_idnum, 1, 1, 1, 2, Qt::AlignLeft);
    diag_layout->addWidget(bt_accept, 2, 0, Qt::AlignRight);
    diag_layout->addWidget(bt_refuse, 2, 2, Qt::AlignLeft);

    entry_name->setPlaceholderText("Enter passager name here");
    entry_idnum->setPlaceholderText("Entry passager id number here");
    entry_name->setAcceptRichText(false);
    entry_idnum->setAcceptRichText(false);
}

int ticket_dialog::exec()
{
    entry_idnum->setText("");
    entry_name->setText("");
    return QDialog::exec();
}

QString ticket_dialog::get_name() const
{
    return entry_name->toPlainText();
}

QString ticket_dialog::get_idnum() const
{
    return entry_idnum->toPlainText();
}

refund_dialog::refund_dialog(QWidget *parent)
    : QDialog(parent)
    , diag_layout(new QGridLayout(this))
    , bt_accept(new QPushButton("Confirm", this))
    , bt_refuse(new QPushButton("Cancel", this))
    , str(new QLabel("Confirm to refund?", this))
{
    setWindowTitle("Refund");
    setFixedSize(200, 125);

    connect(bt_accept, &QPushButton::clicked,
            this, &refund_dialog::accept);
    connect(bt_refuse, &QPushButton::clicked,
            this, &refund_dialog::reject);

//    str->setReadOnly(true);
//    str->setAcceptRichText(false);

    diag_layout->addWidget(str, 0, 0, 1, 2, Qt::AlignCenter);
    diag_layout->addWidget(bt_accept, 1, 0, Qt::AlignCenter);
    diag_layout->addWidget(bt_refuse, 1, 1, Qt::AlignCenter);

    setLayout(diag_layout);
}
