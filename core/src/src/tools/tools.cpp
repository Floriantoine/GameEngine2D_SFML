#include "tools/tools.hpp"

namespace tools {
uint64 stringToId(const char *name, size_t length)
{
    uint64 seed;
    return SpookyHash::Hash64(name, length, seed);
}

uint64 stringToId(const std::string name)
{
    uint64 seed;
    return SpookyHash::Hash64(name.c_str(), name.length(), seed);
}

uint64 stringToId(const std::string name, size_t length)
{
    uint64 seed;
    return SpookyHash::Hash64(name.c_str(), length, seed);
}

std::vector<char *> vStringToChar(std::vector<std::string> strings)
{
    std::vector<char *> array;
    array.reserve(strings.size());

    for (auto &item: strings) {
        array.push_back(const_cast<char *>(item.c_str()));
    }
    return array;
}

} // namespace tools