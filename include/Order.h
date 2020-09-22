#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <nlohmann/json.hpp>

#include <iomanip>

using namespace std;
using json = nlohmann::json;

struct Order
{
    enum Order_t
    {
        BID = 'b',
        ASK = 'a'
    };

    // quadruple precision number format might be best in production cases
    long double price, volume, time;
    Order_t orderType;

    // ctor
    // json::basic_json<>
    Order(const json &, Order_t);

    friend ostream &operator<<(ostream &, const Order &);
};

// toLongDouble - be extremly cautious when using it
long double toLongDouble(const json &);

#endif // ORDER_H