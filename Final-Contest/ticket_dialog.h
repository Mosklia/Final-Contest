#ifndef TICKET_DIALOG_H
#define TICKET_DIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

class ticket_dialog : public QDialog
{
    Q_OBJECT
public:
    ticket_dialog(QWidget *parent);
    QString get_name() const;
    QString get_idnum() const;

public slots:
    int exec();

private:
    QGridLayout *diag_layout;
    QPushButton *bt_accept, *bt_refuse;
    QLabel *label_name, *label_idnum;
    QTextEdit *entry_name, *entry_idnum;
};

class refund_dialog : public QDialog
{
    Q_OBJECT
public:
    refund_dialog(QWidget *parent);

private:
    QGridLayout *diag_layout;
    QPushButton *bt_accept, *bt_refuse;
    QLabel *str;
};

#endif // TICKET_DIALOG_H
