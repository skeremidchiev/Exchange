#include "Order.h"

Order::Order(const json &node, Order_t ot)
{
    price = toLongDouble(node[0]);
    volume = toLongDouble(node[1]);
    time = toLongDouble(node[2]);
    orderType = ot;
}

ostream &
operator<<(ostream &os, const Order &t)
{
    return os << fixed
              << static_cast<char>(t.orderType) << " "
              << setprecision(5) << t.price << " ("
              << setprecision(9) << t.volume << ")\t"
              << t.time;
}

long double
toLongDouble(const json &node)
{
    string str = node.dump();
    return stold(str.substr(1, str.size() - 2));
}