#ifndef UTILS_HPP
#define UTILS_HPP

#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

double toDouble(const json &);

#endif // UTILS_HPP