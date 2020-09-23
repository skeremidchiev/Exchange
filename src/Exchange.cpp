#include "Exchange.h"

Exchange::Exchange(const string &apiUrl, const string &apiData)
    : orders{}
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
    const uint limit = initialMsgs + 10; // change it to capture more msgs

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
            .then([this](string body) {
                cout << "BODY: " << body << "\n\n";
                toOrder(json::parse(body));
            })
            .wait();

        i++;
    }

    orders.print();
}

double toDouble(const json &node)
{
    string str = node.dump();
    return stod(str.substr(1, str.size() - 2));
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
        cout << "OK" << endl;

        // initial book
        if (jsonMsg[1].find("as") != jsonMsg[1].end() && jsonMsg[1].find("bs") != jsonMsg[1].end())
        {
            auto ask = jsonMsg[1]["as"];
            for (auto it = ask.begin(); it != ask.end(); ++it)
            {
                double price = toDouble((*it)[0]);
                double volume = toDouble((*it)[1]);
                double time = toDouble((*it)[2]);
                orders.insert(price, volume, time, Order::ASK);
            };

            auto bid = jsonMsg[1]["bs"];

            for (json::iterator it = bid.begin(); it != bid.end(); ++it)
            {
                double price = toDouble((*it)[0]);
                double volume = toDouble((*it)[1]);
                double time = toDouble((*it)[2]);
                orders.insert(price, volume, time, Order::BID);
            };

            return true;
        }

        if (jsonMsg[1].find("a") != jsonMsg[1].end())
        {
            auto ask = jsonMsg[1]["a"];
            for (auto it = ask.begin(); it != ask.end(); ++it)
            {
                double price = toDouble((*it)[0]);
                double volume = toDouble((*it)[1]);
                double time = toDouble((*it)[2]);
                orders.insert(price, volume, time, Order::ASK);
            };

            return true;
        }

        if (jsonMsg[1].find("b") != jsonMsg[1].end())
        {
            auto ask = jsonMsg[1]["b"];
            for (auto it = ask.begin(); it != ask.end(); ++it)
            {
                double price = toDouble((*it)[0]);
                double volume = toDouble((*it)[1]);
                double time = toDouble((*it)[2]);
                orders.insert(price, volume, time, Order::BID);
            };

            return true;
        }
    }
}
