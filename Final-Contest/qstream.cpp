#include "qstream.h"

QTextStream& operator>>(QTextStream &ist, bool &b)
{
    QString temp = "";
    ist >> temp;

    if (temp == "true")
    {
        b = true;
    }
    else if (temp == "false")
    {
        b = false;
    }
    else
    {
        ist.setStatus(QTextStream::Status::ReadCorruptData);
    }

    return ist;
}

QTextStream& operator<<(QTextStream &ost, bool b)
{
    return ost << (b ? "true" : "false");
}
