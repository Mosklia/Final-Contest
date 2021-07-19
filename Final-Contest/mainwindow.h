#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QAction>
#include <QToolBar>
#include <QMenuBar>

#include "file_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_save_file(const QString &file);
    void on_open_file(const QString &file);
    void on_loadfile_clicked();
    void on_savefile_clicked();
    void on_saveas_clicked();

signals:
    void file_open_failed(const QString &file);
    void readfile_opened(QFile &file);
    void writefile_opened(QFile &file);

private:
//    Ui::MainWindow *ui;
    QFile *data_file;
    open_file_dialog *open_file_diag;
    save_file_dialog *save_file_diag;
    QAction *load_file, *save_file, *save_as;
    QToolBar *tool_bar;
    QMenuBar *menu_bar;

    void initialize_attributes();
    void initialize_ui();
    void initialize_connections();
};
#endif // MAINWINDOW_H
