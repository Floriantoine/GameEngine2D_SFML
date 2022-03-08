#pragma once
#include "Spooky.hpp"
#include <string>

namespace tools {

uint64 stringToId(const char *name, size_t length);
uint64 stringToId(const std::string name);
uint64 stringToId(const std::string name, size_t length);
} // namespace tools