#pragma once

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <memory>
#include <string>

#include <nlohmann/json.hpp>

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
    Order(double p, double v, double id, Order_t ot)
        : price{p}, volume(v), id{id}, orderType(ot)
    {
    }

    // for Kraken id is price, Bitfinex is real id
    double price, volume, id;
    Order_t orderType;

    friend ostream &operator<<(ostream &, const Order &);
};

struct CustomKey
{
    double value;
    Order::Order_t orderType;

    bool operator==(const CustomKey &) const;
};

struct Greater
{
    // ordered from highest ask to lowest bid - asks always on top?
    bool operator()(const CustomKey &a, const CustomKey &b) const;
};
typedef map<CustomKey, Order, Greater> Map_t;

class Orders
{
public:
    Orders() : orders{}, hashOrders{} {}
    ~Orders()
    {
        orders.clear();
        hashOrders.clear();
    }

    void insert(double, double, double, Order::Order_t);

    Map_t getSortedOrders() { return orders; }

    // helper method
    void print();

private:
    // hashOrders is used for fast access
    unordered_map<double, Map_t::iterator> hashOrders;

    // ordered map
    Map_t orders;
};