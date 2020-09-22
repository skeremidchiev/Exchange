#include "Exchange.h"

Exchange::Exchange(const string &apiUrl, const string &apiData)
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
    const uint initialMsgs = 3;
    const uint limit = initialMsgs + 5; // change it to capture more msgs

    uint i = 0;
    bool ok = true;
    // TODO: try catch
    while (limit > i && ok)
    {
        client
            .receive()
            .then([](websocket_incoming_message in_msg) {
                return in_msg.extract_string();
            })
            .then([&ok](string body) {
                cout << "BODY: " << body << "\n\n";
                auto json = json::parse(body);
            })
            .wait();

        i++;
    }
}

bool Exchange::toOrder(const json &jsonMsg)
{
    // stop on error msg
    if (jsonMsg.find("errorMessage") != jsonMsg.end())
    {
        cout << "Error"
             << "\n\n";

        return false;
    }

    if (jsonMsg.find("status") != jsonMsg.end())
    {
        cout << "Dropping Initial Msgs"
             << "\n\n";
        return true;
    }

    if (jsonMsg.size() == 4 &&
        jsonMsg[0] == 270 &&
        jsonMsg[2] == "book-10" &&
        jsonMsg[3] == "XBT/USD")
    {
        cout << jsonMsg[1]["as"] << "\n\n";
        auto ask = jsonMsg[1]["as"];

        for (auto it = ask.begin(); it != ask.end(); ++it)
        {
            std::cout << *it << '\n';

            Order t{*it, Order::ASK};
            auto keyPair = OrdersKey_t{t.price, t.orderType};
            orders.insert(
                pair<OrdersKey_t, Order>(keyPair, t));

            cout << t << "\n";
        };

        cout << jsonMsg[1]["bs"] << "\n\n";

        auto bid = jsonMsg[1]["bs"];

        for (json::iterator it = bid.begin(); it != bid.end(); ++it)
        {
            std::cout << *it << '\n';

            Order t{*it, Order::BID};
            auto keyPair = OrdersKey_t{t.price, t.orderType};
            orders.insert(
                pair<OrdersKey_t, Order>(keyPair, t));

            cout << t << "\n";
        };

        for (auto it = orders.begin(); it != orders.end(); it++)
        {
            auto keyPair = it->first;
            cout << keyPair.first << " " << keyPair.second // string (key)
                 << "\t:\t"
                 << it->second // string's value
                 << std::endl;
        }
    }
}