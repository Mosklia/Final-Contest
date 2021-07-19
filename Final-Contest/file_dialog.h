#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

#include <QFileDialog>
#include <QObject>
#include <QFile>

class open_file_dialog : public QFileDialog
{
    Q_OBJECT

public:
    open_file_dialog(QWidget *parent);
};

class save_file_dialog : public QFileDialog
{
    Q_OBJECT

public:
    save_file_dialog(QWidget *parent);
};

#endif // FILE_DIALOG_H
