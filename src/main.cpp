#include <iostream>
#include <cpprest/ws_client.h>
#include <nlohmann/json.hpp>
#include <map>

#include "Order.h"

using namespace std;
using namespace web;
using namespace web::websockets::client;
using json = nlohmann::json;

typedef pair<long double, Order::Order_t> OrdersKey_t;

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

int main()
{
    websocket_client client;
    client.connect("wss://ws.kraken.com/").wait();

    std::string api_data("{\"event\":\"subscribe\", \"subscription\":{\"name\":\"book\", \"depth\": 10}, \"pair\":[\"BTC/USD\"]}");

    websocket_outgoing_message out_msg;
    out_msg.set_utf8_message(api_data);
    client.send(out_msg).wait();

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

                map<OrdersKey_t, Order, Sorter> m;

                // stop on error msg
                if (json.find("errorMessage") != json.end())
                {
                    cout << "Error"
                         << "\n\n";
                    ok = false;
                    return;
                }

                if (json.find("status") != json.end())
                {
                    cout << "Dropping Initial Msgs"
                         << "\n\n";
                    return;
                }

                if (json.size() == 4 &&
                    json[0] == 270 &&
                    json[2] == "book-10" &&
                    json[3] == "XBT/USD")
                {
                    cout << json[1]["as"] << "\n\n";
                    auto ask = json[1]["as"];

                    for (json::iterator it = ask.begin(); it != ask.end(); ++it)
                    {
                        std::cout << *it << '\n';

                        Order t{*it, Order::ASK};
                        auto keyPair = OrdersKey_t{t.price, t.orderType};
                        m.insert(
                            pair<OrdersKey_t, Order>(keyPair, t));

                        cout << t << "\n";
                    };

                    cout << json[1]["bs"] << "\n\n";

                    auto bid = json[1]["bs"];

                    for (json::iterator it = bid.begin(); it != bid.end(); ++it)
                    {
                        std::cout << *it << '\n';

                        Order t{*it, Order::BID};
                        auto keyPair = OrdersKey_t{t.price, t.orderType};
                        m.insert(
                            pair<OrdersKey_t, Order>(keyPair, t));

                        cout << t << "\n";
                    };

                    for (auto it = m.begin(); it != m.end(); it++)
                    {
                        auto keyPair = it->first;
                        cout << keyPair.first << " " << keyPair.second // string (key)
                             << "\t:\t"
                             << it->second // string's value
                             << std::endl;
                    }
                }
            })
            .wait();

        i++;
    }

    client.close().wait();

    return 0;
}
