#ifndef TICKET_DIALOG_H
#define TICKET_DIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>

class ticket_dialog : public QDialog
{
    Q_OBJECT
public:
    ticket_dialog(QWidget *parent);
};

class refund_dialog : public QDialog
{
    Q_OBJECT
public:
    refund_dialog(QWidget *parent);
};

#endif // TICKET_DIALOG_H
