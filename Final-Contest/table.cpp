#include "qstream.h"
#include "table.h"

table::table()
{
}

void table::read_from(QFile &source)
{
    QTextStream data_stream(&source);

    int capacity;
    data_stream >> capacity;
    __trips.resize(capacity);

    for (auto &x : __trips)
    {
        data_stream >> x;
    }
}

void table::save_to(QFile &target)
{
    QTextStream data_stream(&target);

    data_stream << __trips.size() << '\n';

    for (const auto &x : __trips)
    {
        data_stream << x << '\n';
    }

    data_stream.flush();
}

const std::vector<trip>& table::get_all_trips() const
{
    return __trips;
}

trip& table::get_trip(int index)
{
    return __trips.at(index);
}

table main_table;
