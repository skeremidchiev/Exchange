#pragma once

#include "exchange.hpp"
#include "utils.hpp"

class Kraken : public Exchange
{
public:
    Kraken(int = 10, int = 3);
    virtual ~Kraken() {}

private:
    bool parse(const json &);
    bool jsonToOrders(const json &, const string &, Order::Order_t orderType);
};