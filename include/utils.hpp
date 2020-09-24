#pragma once

#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

double toDouble(const json &);