#include <stdexcept>
#include <algorithm>
#include "trip.h"

seat::seat(bool avaliable, const passager& owner)
    : avaliable(avaliable), owner(owner)
{
}

trip::trip(const QString &id,
           const QDate &departure_date,
           const QTime &departure_time,
           const QString &destination,
           int capacity)
    : __id(id), __departure_date(departure_date)
    , __departure_time(departure_time)
    , __destination(destination)
    , __capacity(capacity)
    , __seats(capacity)
{
}

QString trip::get_id() const
{
    return __id;
}

void trip::set_id(const QString &id)
{
    __id = id;
}

QDate trip::get_departure_date() const
{
    return __departure_date;
}

void trip::set_departure_date(const QDate &departure_date)
{
    __departure_date = departure_date;
}

QTime trip::get_departure_time() const
{
    return __departure_time;
}

void trip::set_departure_time(const QTime &departure_time)
{
    __departure_time = departure_time;
}

QString trip::get_destination() const
{
    return __destination;
}

void trip::set_destination(const QString &destination)
{
    __destination = destination;
}

int trip::get_capacity() const
{
    return __capacity;
}

void trip::set_capacity(int capacity)
{
    __capacity = capacity;
    __seats.resize(capacity);
}

void trip::add_order(const passager &owner, int seat_id)
{
    auto &pos = __seats.at(seat_id);

    if (!pos.avaliable)
    {
        throw std::invalid_argument("The seat is invalid!\n");
    }

    pos.owner = owner;
    pos.avaliable = false;
}

void trip::erase_order(const passager &owner)
{
    for (auto &x : __seats)
    {
        if (x.owner == owner)
        {
            x.avaliable = true;
            x.owner = passager("NULL", "NULL");
        }
    }
}

void trip::erase_order(int seat_id)
{
    __seats.at(seat_id).avaliable = true;
    __seats.at(seat_id).owner = passager("NULL", "NULL");
}

seat_code trip::query_seat(int seat_id) const
{
    if (seat_id < 0 || seat_id >= __capacity)
    {
        return seat_code::invalid;
    }
    else
    {
        return __seats[seat_id].avaliable
                ? seat_code::avaliable
                : seat_code::occupied;
    }
}

int trip::query_avaliable() const
{
    int res = 0;

    for (const auto &x : __seats)
    {
        if (x.avaliable)
        {
            ++res;
        }
    }

    return res;
}

bool trip::operator==(const trip &other) const
{
    return __departure_date == other.__departure_date
            && __departure_time == other.__departure_time;
}

QTextStream& operator<<(QTextStream &ost, const seat &s)
{
    return ost << s.avaliable << ' ' << s.owner;
}

QTextStream& operator>>(QTextStream &ist, seat &s)
{
    return ist >> s.avaliable >> s.owner;
}

QTextStream& operator<<(QTextStream &ost, const trip &t)
{
    ost << t.get_id() << ' ' << t.get_destination() << ' '
        << t.get_capacity() << ' '
        << t.get_departure_date().toString("yyyy-MM-dd") << ' '
        << t.get_departure_time().toString("HH:mm:ss") << '\n';

    for (const auto &x : t.get_all_seats())
    {
        ost << x << '\n';
    }

    return ost;
}

QTextStream& operator>>(QTextStream &ist, trip &t)
{
    QString id, destination, d_date, d_time;
    int capacity;

    ist >> id >> destination >> capacity >> d_date >> d_time;
    t.set_id(id);
    t.set_capacity(capacity);
    t.set_destination(destination);
    t.set_departure_date(QDate::fromString(d_date, "yyyy-MM-dd"));
    t.set_departure_time(QTime::fromString(d_time, "HH:mm:ss"));

    for (int i = 0; i < capacity; ++i)
    {
        seat temp;
        ist >> temp;

        if (temp.avaliable == true)
        {
            t.erase_order(i);
        }
        else
        {
            t.add_order(temp.owner, i);
        }
    }

    return ist;
}

const std::vector<seat>& trip::get_all_seats() const
{
    return __seats;
}
