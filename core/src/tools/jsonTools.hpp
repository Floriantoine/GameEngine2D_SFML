#pragma once

#include "nlohmann/json.hpp"
#include <json/value.h>

namespace json {

nlohmann::json loadJson(const std::string &file)
{
    std::ifstream fd(file);

    if (!fd.good()) {
        return nlohmann::json::value_t::discarded;
    }
    return nlohmann::json::parse(fd, nullptr, false, true);
}

} // namespace json