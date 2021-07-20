#ifndef TICKET_DIALOG_H
#define TICKET_DIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>

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

private:
    QGridLayout *diag_layout;
    QPushButton *bt_accept, *bt_refuse;
    QTextEdit *str;
};

#endif // TICKET_DIALOG_H
