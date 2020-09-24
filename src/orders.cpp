#include "orders.hpp"

/* ******************************
 * Order
 * ****************************** */
ostream &operator<<(ostream &os, const Order &t)
{
    return os << fixed
              << static_cast<char>(t.orderType) << " "
              << setprecision(5) << t.price << " ("
              << setprecision(9) << t.volume << ")\t"
              << "ID: " << t.id;
}

/* ******************************
 * CustomKey
 * ****************************** */

bool CustomKey::operator==(const CustomKey &other) const
{
    return (value == other.value && orderType == other.orderType);
}

/* ******************************
 * Orders
 * ****************************** */
bool Greater::operator()(
    const CustomKey &a,
    const CustomKey &b) const
{
    // have no idea if BID can go over lowest ASK ...
    return a.value > b.value; // && a.orderType < b.orderType;
}

// base case scenario:
// new - O(log n)
// update - O(1)
// delete - O(log n)
void Orders::insert(double price, double volume, double id, Order::Order_t ot)
{
    Order order{price, volume, id, ot};
    CustomKey key{price, ot};

    // delete item - element must exist or something is wrong with API
    if (volume == 0.0)
    {
        orders.erase(hashOrders[id]); // delete from map (complexity - O(log n))
        hashOrders.erase(id);         // delete from unordered map (complexity - O(1))
    }
    else if (hashOrders.find(id) != hashOrders.end()) // find (complexity -best case O(1), worst O(n))
    {
        hashOrders[id]->second = order; // update should be linear
    }
    else // new
    {
        auto iter = orders.insert(make_pair(key, order)); // insert in map (complexity - O(log n))
        hashOrders.insert(make_pair(id, iter.first));     // insert in unordered map (complexity -best case O(1), worst O(n))
    }
}

void Orders::print()
{
    for (auto it = orders.begin(); it != orders.end(); it++)
    {
        auto key = it->first;
        cout << key.value << " " << key.orderType // string (key)
             << " : "
             << it->second // string's value
             << std::endl;
    }

    for (auto it = hashOrders.begin(); it != hashOrders.end(); it++)
    {
        auto key = it->first;
        cout << key   // string (key)
             << " : " // string's value
             << std::endl;
    }

    cout << "out of print" << endl;
}