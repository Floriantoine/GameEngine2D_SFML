#pragma once
#include "Spooky.hpp"
#include <string>
#include <vector>

namespace tools {

uint64 stringToId(const char *name, size_t length);
uint64 stringToId(const std::string name);
uint64 stringToId(const std::string name, size_t length);
std::vector<char *> vStringToChar(std::vector<std::string> strings);
} // namespace tools