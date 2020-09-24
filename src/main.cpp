#include "kraken.hpp"
#include "bitfinex.hpp"
#include "orderbook.hpp"

int main()
{
    Orderbook ob{};

    Kraken kr{
        "wss://ws.kraken.com/",
        "{\"event\":\"subscribe\", \"subscription\":{\"name\":\"book\", \"depth\": 25}, \"pair\":[\"BTC/USD\"]}",
        10};

    Bitfinex bf{
        "wss://api.bitfinex.com/ws/2",
        "{\"event\":\"subscribe\", \"channel\":\"book\", \"pair\":\"tBTCUSD\", \"prec\":\"R0\", \"len\":\"25\"}",
        10};

    kr.subscribe(ob);
    bf.subscribe(ob);

    kr.receive();
    bf.receive();

    cout << "DONE" << endl;

    return 0;
}
