#ifndef BITFINEX_HPP
#define BITFINEX_HPP

#include "exchange.hpp"
#include "utils.hpp"

class Bitfinex : public Exchange
{
public:
    Bitfinex(const string &, const string &, int, int = 3);
    virtual ~Bitfinex() {}

private:
    bool parse(const json &);

    int chainID;
};

#endif // BITFINEX_HPP