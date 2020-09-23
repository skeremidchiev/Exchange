#ifndef KRAKEN_HPP
#define KRAKEN_HPP

#include "exchange.hpp"
#include "utils.hpp"

class Kraken : public Exchange
{
public:
    Kraken(const string &, const string &, int, int = 3);
    virtual ~Kraken() {}

private:
    bool parse(const json &);
    bool jsonToOrders(const json &, const string &, Order::Order_t orderType);
};

#endif // KRAKEN_HPP