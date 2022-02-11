#pragma once

#include "Imgui.hpp"
#include "Spooky.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>

namespace tools {

class Chrono {
  private:
    static inline std::chrono::_V2::system_clock::time_point _start;
    static inline std::unordered_map<uint64, std::vector<float>> _values;

  public:
    static void start();
    static void end(std::string name);
    static void end();

    Chrono(/* args */);
    ~Chrono() = default;
    static uint64 nameToId(std::string name);
    static uint64 nameToId(const char *name, size_t length);
    static std::vector<float> *GetValuesList(uint64 id);
    static bool isRegistered(uint64 id);
};

} // namespace tools