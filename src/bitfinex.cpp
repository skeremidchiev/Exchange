#include "bitfinex.hpp"

Bitfinex::Bitfinex(
    const string &apiUrl,
    const string &apiData,
    int msgLimit,
    int initialMsgCount)
    : Exchange(apiUrl, apiData, msgLimit + initialMsgCount)
{
}

bool Bitfinex::parse(const json &jsonMsg)
{
    // drop status msgs and error msg
    if (jsonMsg.find("event") != jsonMsg.end())
    {
        if (jsonMsg.find("chanId") != jsonMsg.end())
        {
            chainID = jsonMsg["chanId"];
        }

        return false;
    }

    if (jsonMsg[0] == chainID)
    {
        // For Trading: if AMOUNT > 0 then bid else ask
        auto getOrderType = [](double volume) {
            return (volume > 0) ? Order::Order_t::BID : Order::Order_t::ASK;
        };

        auto insert = [=](json js) {
            double id = js[0];
            double price = js[1];
            double volume = js[2];

            // trigger delete
            if (price == 0.0 && (volume == -1 || volume == 1))
            {
                // force delete by passing 0 to volume
                orders.insert(price, 0, id, getOrderType(volume));
            }
            else
            {
                // update or insert
                orders.insert(price, abs(volume), id, getOrderType(volume));
            }
        };

        auto data = jsonMsg[1];
        if (data[0].is_array())
        {
            // Why multiple entries in book have the same price but different id and volume?
            // Can't find clear info about it so I assume it's the same as kraken - update of volume.
            for (auto it = data.begin(); it != data.end(); ++it)
            {
                insert(*it);
            };
        }
        else
        {
            insert(data);
        }
    }
    return true;
}
