#pragma once

#include "exchange.hpp"
#include <set>

class Orderbook : public Observer<Exchange>
{
public:
    Orderbook() {}
    virtual ~Orderbook() {}

    void msg_received(Exchange &);

    void print();

private:
    set<pair<double, double>, greater<pair<double, double>>> bidOrders;
    set<pair<double, double>, greater<pair<double, double>>> askOrders;
};