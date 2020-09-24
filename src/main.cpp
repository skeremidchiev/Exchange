#include "kraken.hpp"
#include "bitfinex.hpp"
#include "orderbook.hpp"

int main()
{
    Orderbook ob{};

    Kraken kr{10};
    kr.subscribe(ob);

    Bitfinex bf{10};
    bf.subscribe(ob);

    kr.receive();
    bf.receive();

    return 0;
}
