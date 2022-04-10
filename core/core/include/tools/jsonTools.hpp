#pragma once

#include "nlohmann/json.hpp"
#include <fstream>

namespace json {

nlohmann::json loadJson(const std::string &file);

} // namespace json