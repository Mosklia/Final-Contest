#include "file_dialog.h"

open_file_dialog::open_file_dialog(QWidget *parent)
    : QFileDialog(parent, "Choose the file to load")
{
    setFileMode(QFileDialog::ExistingFile);
    setAcceptMode(QFileDialog::AcceptOpen);
}

save_file_dialog::save_file_dialog(QWidget *parent)
    : QFileDialog(parent, "Choose the file to save")
{
    setFileMode(QFileDialog::AnyFile);
    setAcceptMode(QFileDialog::AcceptSave);
}
