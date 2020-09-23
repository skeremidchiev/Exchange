#include "kraken.hpp"
#include "bitfinex.hpp"

int main()
{
    // Kraken kr{
    //     "wss://ws.kraken.com/",
    //     "{\"event\":\"subscribe\", \"subscription\":{\"name\":\"book\", \"depth\": 25}, \"pair\":[\"BTC/USD\"]}",
    //     10};

    // kr.receive();
    {
        Bitfinex bf{
            "wss://api.bitfinex.com/ws/2",
            "{\"event\":\"subscribe\", \"channel\":\"book\", \"pair\":\"tBTCUSD\", \"prec\":\"R0\", \"len\":\"25\"}",
            10};

        bf.receive();
    }
    cout << "outside" << endl;

    return 0;
}
