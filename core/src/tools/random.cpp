#include <SFML/System/Vector2.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

namespace tools {

int generate_random_number(int min, int max, int nop)
{
    int out_rand = nop;

    while (out_rand < min || out_rand > max || out_rand == nop) {
        out_rand = std::rand() % ((max - min) == 0 ? 1 : (max - min)) + min;
    }
    return (out_rand);
}

int generate_random_number(int min, int max)
{
    int out_rand = max + 1;

    if (min == max || min > max)
        return min;

    while (out_rand < min || out_rand > max) {
        out_rand = std::rand() % ((max - min) == 0 ? 1 : (max - min)) + min;
    }
    return (out_rand);
}

float generate_random_number(float min, float max)
{
    float out_rand = max + 1;
    float toFloat = generate_random_number(0, 100) / 100.00;
    int value = static_cast<int>((max - min));
    if (value == 0)
        value = 1;

    if (min == max || min > max)
        return min;

    while (out_rand - toFloat < min || out_rand - toFloat > max) {
        out_rand = static_cast<float>(std::rand() % value + min);
        toFloat = generate_random_number(-100, 100) / 100.00;
    }
    return (out_rand)-toFloat;
}

} // namespace tools
