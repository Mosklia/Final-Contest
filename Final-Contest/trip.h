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
#include "qstream.h"
#include "passager.h"

struct seat
{
    bool avaliable;
    passager owner;

    seat(bool avaliable = true,
         const passager &owner = passager());

};

QTextStream& operator<<(QTextStream &ost, const seat &s);
QTextStream& operator>>(QTextStream &ist, seat &s);

enum class seat_code
{
    avaliable = 0,
    occupied = 1,
    invalid = 2
};

//class trip : public QObject
class trip
{
//    Q_OBJECT

public:
    trip(const QString &id = "NULL",
         const QDate &departure_date = QDate(),
         const QTime &departure_time = QTime(),
         const QString &destination = "NULL",
         int capacity = 1);

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

    bool operator==(const trip &other) const;
//    trip& operator=(const trip &other) = default;

    // Query the statue of a seat.
    // Always run this before operating the seats.
    seat_code query_seat(int seat_id) const;

    // Return a reference to a std::vector that contains ALL the seats.
    // NEVER TRY TO MODIFY THIS VECTOR DIRECTLY!
    const std::vector<seat>& get_all_seats() const;

    seat& get_seat(int index);

    // rnm, refund my money!
    void erase_order(const passager &owner);
    void erase_order(int seat_id);

    // Query for how many seats are avaliable.
    int query_avaliable() const;

//public slots:
    // Add a user to the trip.
    // When the place is unavaliable, the function throws an exception.
    // Note that the id of seats starts with 0.
    void add_order(const passager &owner, int seat_id);

private:
    QString __id; // __id: number of the trip
    QDate __departure_date;
    QTime __departure_time;
    QString __destination;
    int __capacity;
    std::vector<seat> __seats;
};

QTextStream& operator<<(QTextStream &ost, const trip &t);
QTextStream& operator>>(QTextStream &ist, trip &t);

#endif // TRIP_H
