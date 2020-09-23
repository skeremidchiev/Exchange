#ifndef EXCHANGE_HPP
#define EXCHANGE_HPP

#include "orders.hpp"

#include <cpprest/ws_client.h>

using namespace web;
using namespace web::websockets::client;

class Exchange
{
public:
    Exchange(const string &, const string &, int);
    virtual ~Exchange();

    void receive();

protected:
    Orders orders;

private:
    void connect(const string &, const string &);
    virtual bool parse(const json &) = 0;

    websocket_client client;
    int msgLimit;
};

#endif // EXCHANGE_HPP