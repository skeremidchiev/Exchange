#include "utils.hpp"

double toDouble(const json &node)
{
    string str = node.dump();
    return stod(str.substr(1, str.size() - 2));
}
