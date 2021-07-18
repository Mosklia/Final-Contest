#ifndef QSTREAM_H
#define QSTREAM_H

#include <QTextStream>

QTextStream& operator<<(QTextStream &ost, bool b);
QTextStream& operator>>(QTextStream &ist, bool &b);

#endif // QSTREAM_H
