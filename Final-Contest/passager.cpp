#include "passager.h"

passager::passager(const QString &name, const QString &pid)
    : __name(name), __pid(pid)
{
}

QString passager::get_name() const
{
    return __name;
}

void passager::set_name(const QString &name)
{
    __name = name;
}

QString passager::get_pid() const
{
    return __pid;
}

void passager::set_pid(const QString &pid)
{
    __pid = pid;
}

bool passager::operator==(const passager &other) const
{
    return __pid == other.__pid;
}

QTextStream& operator<<(QTextStream &ost, const passager &p)
{
    ost << p.get_name() << ' ' << p.get_pid();
    return ost;
}

QTextStream& operator>>(QTextStream &ist, passager &p)
{
    QString temp_name, temp_pid;
    ist >> temp_name >> temp_pid;

    p.set_name(temp_name);
    p.set_pid(temp_pid);

    return ist;
}
