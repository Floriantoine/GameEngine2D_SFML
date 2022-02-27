#pragma once

#include "tools/jsonTools.hpp"
#include <variant>
struct MouseClick
{
    int x;
    int y;
};

struct MouseMove
{
    int x;
    int y;
};

struct KeyPressed
{
    int key;
};

struct NewEntity
{
    std::string configPath;
};

struct RandomEvent
{
};

using Event =
    std::variant<MouseClick, MouseMove, KeyPressed, RandomEvent, NewEntity>;