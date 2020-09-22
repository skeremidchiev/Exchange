#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "Order.h"

#include <cpprest/ws_client.h>
#include <unordered_map>

using namespace web;
using namespace web::websockets::client;

class Exchange
{
public:
    Exchange(const string &, const string &);
    ~Exchange();

    typedef pair<long double, Order::Order_t> OrdersKey_t;

private:
    void connect(const string &, const string &);
    void receive();
    bool toOrder(const json &);

    struct Sorter
    {
        // ordered from highest ask to lowest bid
        // not really clear whether `asks` should always be on top
        bool operator()(OrdersKey_t a, OrdersKey_t b)
        {
            if (a.first == b.first)
            {
                return a.second < b.second;
            }

            return a.first > b.first;
        }
    };

    map<OrdersKey_t, Order, Sorter> orders;

    websocket_client client;
};

#endif // EXCHANGE_H