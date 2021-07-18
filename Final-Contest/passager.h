#ifndef PASSAGER_H
#define PASSAGER_H

#include <QObject>
#include <QString>
#include "qstream.h"

class passager
{
    Q_OBJECT

public:
    // Constructor
    passager(const QString &name = QString("NULL"), const QString &pid = QString("NULL"));

    // Get and set functions
    void set_pid(const QString &pid);
    QString get_pid() const;

    void set_name(const QString &name);
    QString get_name() const;

    bool operator==(const passager &other) const;

private:
    QString __name, __pid;
};

QTextStream& operator<<(QTextStream &ost, const passager &p);
QTextStream& operator>>(QTextStream &ist, passager &p);

// Compares whether @other is equal to @elem.
template <typename __tp>
struct equal_to
{
    __tp elem;

    equal_to(const __tp &elem) : elem(elem) {}
    bool operator()(const __tp &other) const
    {
        return elem == other;
    }
};

#endif // PASSAGER_H
