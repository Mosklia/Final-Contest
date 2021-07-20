#ifndef TRIP_DIALOG_H
#define TRIP_DIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QTableView>
#include "table.h"
#include "ticket_dialog.h"
#include "qstream.h"

class blank_delegate : public QStyledItemDelegate
{
    Q_OBJECT
signals:
    void created_blank_delegate(const QModelIndex &val) const;

public:
    blank_delegate(QWidget *parent = nullptr) : QStyledItemDelegate(parent) {}

    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &index) const override
    {
        emit created_blank_delegate(index);
        return nullptr;
    }
};

class trip_dialog : public QDialog
{
    Q_OBJECT

public:
    trip_dialog(QWidget *parent = nullptr);

    void execute(trip &source);

    ~trip_dialog();

signals:
    void refund_requested();
    void order_requested();

private slots:
    void selection_changed();
    void on_button_click();
    void reload_model();

private:
    trip *data;
    QVBoxLayout *diag_layout;
    QPushButton *change_button;
    ticket_dialog *order_diag;
    refund_dialog *refund_diag;
    QStandardItemModel *model;
    QTableView *view;
    blank_delegate *delegate;
};

#endif // TRIP_DIALOG_H
