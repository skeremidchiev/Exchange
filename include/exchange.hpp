#pragma once

#include "orders.hpp"
#include "observer.hpp"

// issues in websocket - cpprest/ws_client.h
// exception on closing
#include <cpprest/ws_client.h>

using namespace web;
using namespace web::websockets::client;

class Exchange : public Observable<Exchange>
{
public:
    Exchange(const string &, const string &, int);
    virtual ~Exchange();

    void receive();

    Orders getOrders() { return orders; }

protected:
    Orders orders;

private:
    void connect(const string &, const string &);
    virtual bool parse(const json &) = 0;

    websocket_client client;
    int msgLimit;
};