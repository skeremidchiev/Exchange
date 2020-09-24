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
    map<double, double, greater<double>> bidOrders;
    map<double, double, greater<double>> askOrders;
};