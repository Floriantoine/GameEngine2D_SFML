
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class mainClass {
  private:
    /* data */
  public:
    sf::RenderWindow _window;
    sf::Event _event;
    sf::RenderWindow *getWinRef();
    void eventPoll();
    mainClass();
    ~mainClass();
};

sf::RenderWindow *mainClass::getWinRef()
{
    return &_window;
}

void mainClass::eventPoll()
{
    while (_window.pollEvent(_event)) {
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        // _window.close();
        if (_event.type == sf::Event::Closed) {
            _window.close();
        }
        if (_event.type == sf::Event::KeyPressed &&
            _event.key.code == sf::Keyboard::Escape)
            _window.close();
    }
}

mainClass::mainClass() : _window(sf::VideoMode(1920, 1080), "HUNTER"), _event()
{
}

mainClass::~mainClass()
{
}
