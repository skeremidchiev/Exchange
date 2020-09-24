
#include "orderbook.hpp"

void Orderbook::msg_received(Exchange &source)
{
    // aggregation of the data is not a cheap operation
    // complexity of such aproach is really high O(n*log n)
    // this will get slower with more elements in the structure
    // not sure if this is the goal of the task???
    auto ords = source.getOrders().getSortedOrders();
    for (auto i = ords.begin(); i != ords.end(); i++)
    {
        auto data = i->second;
        if (data.orderType == Order::BID)
        {
            bidOrders.insert(make_pair(data.price, data.volume));
        }
        else
        {
            askOrders.insert(make_pair(data.price, data.volume));
        }
    }

    print();
}

void Orderbook::print()
{
    auto beautyPrint = [](const string &str, double price, double volume) {
        cout << left << setw(10) << str
             << setw(10) << price
             << setw(10) << volume
             << endl;
    };

    cout << "bids:" << endl;
    for (auto i = bidOrders.begin(); i != bidOrders.end(); i++)
    {
        beautyPrint("", i->first, i->second);
    }
    auto bestBid = bidOrders.begin();
    beautyPrint("best bid", bestBid->first, bestBid->second);

    cout << "asks:" << endl;
    for (auto i = askOrders.begin(); i != askOrders.end(); i++)
    {
        beautyPrint("", i->first, i->second);
    }
    auto bestAsk = askOrders.rbegin();
    beautyPrint("best ask", bestAsk->first, bestAsk->second);
}