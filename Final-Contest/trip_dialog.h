#ifndef TRIP_DIALOG_H
#define TRIP_DIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QStyledItemDelegate>
#include "table.h"
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

    void execute(const trip &source);

private:
};

#endif // TRIP_DIALOG_H
