#pragma once

#include "Imgui.hpp"
#include "Spooky.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

namespace tools {

struct ImplotPerfInf
{
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    std::string _name;
    int Plt;
    float _maxValue = 0;
    float _minValue = 0;
    bool isPlot = false;
    ImplotPerfInf(std::string name, int max_size = 2000)
    {
        MaxSize = max_size;
        Offset = 0;
        Data.reserve(MaxSize);
        _name = name;
        Plt = -1;
    }
    ImplotPerfInf(int max_size = 2000)
    {
        MaxSize = max_size;
        Offset = 0;
        Data.reserve(MaxSize);
        _name = std::string("#");
        Plt = -1;
    }
    void AddPoint(float x, float y)
    {
        if (y > _maxValue)
            _maxValue = y;
        if (y < _minValue)
            _minValue = y;
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x, y));
        else {
            Data[Offset] = ImVec2(x, y);
            Offset = (Offset + 1) % MaxSize;
        }
    }
    void Erase()
    {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset = 0;
        }
    }
};

class Chrono {
  private:
    static inline float t = 0;
    static inline std::vector<std::chrono::_V2::system_clock::time_point>
        _starts;
    static inline std::unordered_map<uint64, ImplotPerfInf> _values;

  public:
    static void start();
    static void end(std::string name);
    static void end();
    static void event(std::string name);
    static void display();

    Chrono(/* args */);
    ~Chrono();
    static uint64 nameToId(std::string name);
    static uint64 nameToId(const char *name, size_t length);
    static ImplotPerfInf *GetValuesList(std::string name);
    static bool isRegistered(uint64 id);
};

} // namespace tools