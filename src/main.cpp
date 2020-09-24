#include "kraken.hpp"
#include "bitfinex.hpp"
#include "orderbook.hpp"

int main()
{
    Orderbook ob{};

    Kraken kr{
        "wss://ws.kraken.com/",
        "{\"event\":\"subscribe\", \"subscription\":{\"name\":\"book\", \"depth\": 10}, \"pair\":[\"BTC/USD\"]}",
        10};
    kr.subscribe(ob);

    Bitfinex bf{
        "wss://api.bitfinex.com/ws/2",
        "{\"event\":\"subscribe\", \"channel\":\"book\", \"pair\":\"tBTCUSD\", \"prec\":\"R0\", \"len\":\"25\"}",
        10};
    bf.subscribe(ob);

    kr.receive();
    bf.receive();

    return 0;
}
