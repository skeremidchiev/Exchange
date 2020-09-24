#include "exchange.hpp"

Exchange::Exchange(const string &apiUrl, const string &apiData, int msgLimit = 10)
    : orders{}, msgLimit{msgLimit}
{
    connect(apiUrl, apiData);
}

Exchange::~Exchange()
{
    client.close().wait();
}

void Exchange::connect(const string &apiUrl, const string &apiData)
{
    client.connect(apiUrl).wait();
    websocket_outgoing_message out_msg;

    out_msg.set_utf8_message(apiData);
    client.send(out_msg).wait();
}

void Exchange::receive()
{
    uint i = 0;
    // TODO: try catch
    while (msgLimit > i)
    {
        client
            .receive()
            .then([](websocket_incoming_message in_msg) {
                return in_msg.extract_string();
            })
            .then([this](string body) {
                parse(json::parse(body));
            })
            .wait();

        i++;
    }

    // TODO: remove
    orders.print();
}