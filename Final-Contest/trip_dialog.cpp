#include "trip_dialog.h"

trip_dialog::trip_dialog(QWidget *parent)
    : QDialog(parent)
{

}

void trip_dialog::execute(const trip &source)
{
    exec();
}
