#include "Exchange.h"

int main()
{

    Exchange ex{
        "wss://ws.kraken.com/",
        "{\"event\":\"subscribe\", \"subscription\":{\"name\":\"book\", \"depth\": 10}, \"pair\":[\"BTC/USD\"]}"};

    ex.receive();

    return 0;
}
