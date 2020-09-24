#include "kraken.hpp"

Kraken::Kraken(
    const string &apiUrl,
    const string &apiData,
    int msgLimit,
    int initialMsgCount)
    : Exchange(apiUrl, apiData, msgLimit + initialMsgCount)
{
}

bool Kraken::parse(const json &jsonMsg)
{
    // stop on error msg
    if (jsonMsg.find("errorMessage") != jsonMsg.end())
    {
        return false;
    }

    // drop status msgs
    if (jsonMsg.find("status") != jsonMsg.end())
    {
        return false;
    }

    // all this data checks are hard coded
    if (jsonMsg.size() == 4 &&
        jsonMsg[0] == 270 &&
        // jsonMsg[2] == "book-25" &&
        jsonMsg[3] == "XBT/USD")
    {
        auto data = jsonMsg[1];

        // initial book
        if (jsonToOrders(data, "as", Order::ASK) && jsonToOrders(data, "bs", Order::BID))
        {
            return true;
        }

        // ask
        if (jsonToOrders(data, "a", Order::ASK))
        {
            return true;
        }

        // bid
        if (jsonToOrders(data, "b", Order::BID))
        {
            return true;
        }
    }
}

bool Kraken::jsonToOrders(const json &jsonMsg, const string &name, Order::Order_t orderType)
{
    if (jsonMsg.find(name) != jsonMsg.end())
    {
        auto ask = jsonMsg[name];
        for (auto it = ask.begin(); it != ask.end(); ++it)
        {
            double price = toDouble((*it)[0]);
            double volume = toDouble((*it)[1]);
            // kraken has no id on orders - instead use price
            orders.insert(price, volume, price, orderType);
        };

        return true;
    }

    return false;
}