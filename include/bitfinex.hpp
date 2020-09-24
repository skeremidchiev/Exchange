#pragma once

#include "exchange.hpp"
#include "utils.hpp"

class Bitfinex : public Exchange
{
public:
    Bitfinex(int = 10, int = 3);
    virtual ~Bitfinex() {}

private:
    bool parse(const json &);

    int chainID;
};