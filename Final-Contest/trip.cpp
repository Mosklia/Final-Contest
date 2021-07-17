#include <stdexcept>
#include <algorithm>
#include "trip.h"

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
            x.owner = passager("", "");
        }
    }
}

void trip::erase_order(int seat_id)
{
    __seats.at(seat_id).avaliable = true;
    __seats.at(seat_id).owner = passager("", "");
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
