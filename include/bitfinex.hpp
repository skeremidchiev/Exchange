#pragma once

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