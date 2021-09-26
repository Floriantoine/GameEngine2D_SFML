#include <main.hpp>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    mainClass mainClass;

    mainClass._window.setFramerateLimit(200);
    while (mainClass._window.isOpen()) {
        mainClass._window.clear(sf::Color(rand(), rand(), rand()));
        mainClass.eventPoll();
        mainClass._window.display();
        mainClass._window.clear();
    }

    return 0;
}
