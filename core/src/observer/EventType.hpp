#pragma once

#include <variant>
struct MouseClick
{
    int x;
    int y;
};

struct KeyPressed
{
    int key;
};

struct RandomEvent
{
};

using Event = std::variant<MouseClick, KeyPressed, RandomEvent>;