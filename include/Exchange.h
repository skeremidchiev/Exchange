#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "Orders.h"

#include <cpprest/ws_client.h>
#include <unordered_map>
#include <functional>

using namespace web;
using namespace web::websockets::client;

class Exchange
{
public:
    Exchange(const string &, const string &);
    ~Exchange();

    void receive();

private:
    void connect(const string &, const string &);
    bool toOrder(const json &);

    websocket_client client;
    Orders orders;
};

#endif // EXCHANGE_H