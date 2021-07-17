// Two trips are the same, when and only when both their
// __id and __departure_date are same.

#ifndef TRIP_H
#define TRIP_H

#include <vector>
#include <QObject>
#include <QString>
#include <QDate>
#include <QTime>
#include <QPointer>
#include "passager.h"

struct seat
{
    bool avaliable;
    passager owner;

    seat(bool avaliable = true,
         const passager &owner = passager("", ""));

};

std::ostream& operator<<(std::ostream &ost, const seat &s);
std::istream& operator>>(std::istream &ist, seat &s);

enum class seat_code
{
    avaliable = 0,
    occupied = 1,
    invalid = 2
};

class trip
{
    Q_OBJECT

public:
    trip(const QString &id,
         const QDate &departure_date,
         const QTime &departure_time,
         const QString &destination,
         int capacity);

    // Gets and sets.
    QString get_id() const;
    void set_id(const QString &id);

    QDate get_departure_date() const;
    void set_departure_date(const QDate &departure_date);

    QTime get_departure_time() const;
    void set_departure_time(const QTime &departure_time);

    QString get_destination() const;
    void set_destination(const QString &destination);

    int get_capacity() const;
    void set_capacity(int capacity);

    // Add a user to the trip.
    // When the place is unavaliable, the function throws an exception.
    // Note that the id of seats starts with 0.
    void add_order(const passager &owner, int seat_id);

    // Query the statue of a seat.
    // Always run this before operating the seats.
    seat_code query_seat(int seat_id) const;

    // Return a reference to a std::vector that contains ALL the seats.
    // NEVER TRY TO MODIFY THIS VECTOR DIRECTLY!
    const std::vector<seat>& get_all_seats() const;

    // rnm, refund my money!
    void erase_order(const passager &owner);
    void erase_order(int seat_id);

    // Query for how many seats are avaliable.
    int query_avaliable() const;

private:
    QString __id; // __id: number of the trip
    QDate __departure_date;
    QTime __departure_time;
    QString __destination;
    int __capacity;
    std::vector<seat> __seats;
};

#endif // TRIP_H