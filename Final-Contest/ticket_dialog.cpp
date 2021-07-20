#include "ticket_dialog.h"

ticket_dialog::ticket_dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("ORDER!");
}

refund_dialog::refund_dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("REFUND!");
}
