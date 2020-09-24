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
    try
    {
        client.connect(apiUrl).wait();
        websocket_outgoing_message out_msg;

        out_msg.set_utf8_message(apiData);
        client.send(out_msg).wait();
    }
    catch (const std::exception &e)
    {
        std::cout << "ERROR:" << e.what() << endl;
    }
}

void Exchange::receive()
{
    uint i = 0;

    while (msgLimit > i)
    {
        try
        {
            client
                .receive()
                .then([](websocket_incoming_message in_msg) {
                    return in_msg.extract_string();
                })
                .then([this](string body) {
                    if (parse(json::parse(body)))
                    {
                        notify(*this);
                    }
                })
                .wait();
        }
        catch (const std::exception &e)
        {
            std::cout << "ERROR:" << e.what() << endl;
        }

        i++;
    }
}