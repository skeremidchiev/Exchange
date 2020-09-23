#include "Orders.h"

/* ******************************
 * Orders
 * ****************************** */
bool Orders::Greater::operator()(
    const CustomKey &a,
    const CustomKey &b) const
{
    // have no idea if BID can go over lowest ASK ...
    return a.value > b.value; // && a.orderType < b.orderType;
}

ostream &operator<<(ostream &os, const Order &t)
{
    return os << fixed
              << static_cast<char>(t.orderType) << " "
              << setprecision(5) << t.price << " ("
              << setprecision(9) << t.volume << ")\t"
              << t.time;
}

/* ******************************
 * CustomKey
 * ****************************** */

bool CustomKey::operator==(const CustomKey &other) const
{
    return (value == other.value && orderType == other.orderType);
}

size_t hash<CustomKey>::operator()(const CustomKey &k) const
{
    return (hash<double>()(k.value) ^ (hash<Order::Order_t>()(k.orderType) << 1)) >> 1;
}

/* ******************************
 * Orders
 * ****************************** */

void Orders::insert(double price, double volume, double time, Order::Order_t ot)
{
    Order order{price, volume, time, ot};
    CustomKey key{price, ot};

    // delete item - element must exist or something is wrong with API
    if (volume == 0.0)
    {
        orders.erase(hashOrders[key]); // delete from map (complexity - O(log n))
        hashOrders.erase(key);         // delete from unordered map (complexity - O(1))
    }
    else if (hashOrders.find(key) != hashOrders.end()) // find (complexity -best case O(1), worst O(n))
    {
        hashOrders[key]->second = order; // update should be linear
    }
    else // new
    {
        auto iter = orders.insert(make_pair(key, order)); // insert in map (complexity - O(log n))
        hashOrders.insert(make_pair(key, iter.first));    // insert in unordered map (complexity -best case O(1), worst O(n))
    }
}

void Orders::print()
{
    cout << "ORDERS " << orders.size() << "\n";
    for (auto it = orders.begin(); it != orders.end(); it++)
    {
        auto key = it->first;
        cout << key.value << " " << key.orderType // string (key)
             << "\t:\t"
             << it->second // string's value
             << std::endl;
    }
}