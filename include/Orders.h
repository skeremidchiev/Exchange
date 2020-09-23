#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <nlohmann/json.hpp>
#include <iomanip>

#include <unordered_map>
#include <memory>
#include <string>

using namespace std;
using json = nlohmann::json;

struct Order
{
    enum Order_t
    {
        BID = 'b',
        ASK = 'a'
    };

    // ctor
    Order(double p, double v, double t, Order_t ot)
        : price{p}, volume(v), time{t}, orderType(ot)
    {
    }

    // maybe long double is better option
    // but double is enough for testing
    double price, volume, time;
    Order_t orderType;

    friend ostream &operator<<(ostream &, const Order &);
};

struct CustomKey
{
    double value;
    Order::Order_t orderType;

    bool operator==(const CustomKey &) const;
};

// forced to add the namespace due to explicit specialization
namespace std
{

template <>
struct hash<CustomKey>
{
    size_t operator()(const CustomKey &k) const;
};

} // namespace std

class Orders
{
public:
    Orders() : orders{}, hashOrders{} {}
    ~Orders() {}

    void insert(double, double, double, Order::Order_t);

    // TODO: remove
    void print();

private:
    struct Greater
    {
        // ordered from highest ask to lowest bid - asks always on top?
        bool operator()(const CustomKey &a, const CustomKey &b) const;
    };
    typedef map<CustomKey, Order, Greater> Map_t;

    // hashOrders is used for fast access
    unordered_map<CustomKey, Map_t::iterator> hashOrders;

    // ordered map
    Map_t orders;
};

#endif // ORDER_H