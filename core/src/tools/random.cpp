/*
** EPITECH PROJECT, 2018
** CPE_dante_2018
** File description:
** randy.c
*/

#include <SFML/System/Vector2.hpp>
#include <ctime>
#include <string>
#include <vector>

namespace tools {

int generate_random_number(int min, int max, int nop)
{
    int out_rand = nop;

    while (out_rand < min || out_rand > max || out_rand == nop) {
        out_rand = std::rand() % (max - min) + min;
    }
    return (out_rand);
}

int generate_random_number(int min, int max)
{
    int out_rand = max + 1;

    if (min == max)
        return min;

    while (out_rand < min || out_rand > max) {
        out_rand = std::rand() % (max - min) + min;
    }
    return (out_rand);
}

} // namespace tools
