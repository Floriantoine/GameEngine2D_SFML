/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Event System
*/

#include "EventSystem.hpp"

#include "./Game.hpp"
#include "SFML/Window/Event.hpp"

namespace Game {

void EventSystem::update(long elapsedTime)
{
    sf::Window *window = Game::getInstance().getWindow();
    sf::Event evt;

    while (window->pollEvent(evt)) {
        this->handleCloseEvent(evt);
        this->handleMouseMove(evt);
        this->handleMouseButtonPressedEvents(evt);
        this->handleMouseButtonReleasedEvents(evt);
        this->handleKeyPressedEvents(evt);
        this->handleKeyReleasedEvents(evt);
    }
}

void EventSystem::handleCloseEvent(const sf::Event &evt)
{
    if (evt.type != sf::Event::EventType::Closed)
        return;
    this->_subject->CreateMessage("Close Event");

    Game::getInstance().getWindow()->close();
    Game::getInstance().stop();
}

void EventSystem::handleMouseMove(const sf::Event &evt)
{
    if (evt.type != sf::Event::EventType::MouseMoved)
        return;
}

void EventSystem::handleMouseButtonPressedEvents(const sf::Event &evt)
{
    if (evt.type != sf::Event::EventType::MouseButtonPressed)
        return;
    this->_subject->CreateMessage("Mousse btn!");
}

void EventSystem::handleMouseButtonReleasedEvents(const sf::Event &evt)
{
    if (evt.type != sf::Event::EventType::MouseButtonReleased)
        return;
}

void EventSystem::handleKeyPressedEvents(const sf::Event &evt)
{
    if (evt.type != sf::Event::EventType::KeyPressed)
        return;
    this->_subject->CreateMessage("Key Pressed");

    if (evt.key.code == sf::Keyboard::Left) {
        parallax::ParallaxSystem &parallaxSys =
            Game::getInstance().getParallax();
        parallaxSys.setRate(parallaxSys.getRate() - 1);
    }
    if (evt.key.code == sf::Keyboard::Right) {
        parallax::ParallaxSystem &parallaxSys =
            Game::getInstance().getParallax();
        parallaxSys.setRate(parallaxSys.getRate() + 1);
    }
    if (evt.key.code == sf::Keyboard::Enter) {
        parallax::ParallaxSystem &parallaxSys =
            Game::getInstance().getParallax();
        if (parallaxSys.getConfigName() == "background")
            parallaxSys.initFromFile(
                "../core/json/backConfig.json", "background2");
        else if (parallaxSys.getConfigName() == "background2")
            parallaxSys.initFromFile(
                "../core/json/backConfig.json", "background3");
        else
            parallaxSys.initFromFile(
                "../core/json/backConfig.json", "background");
    }
}

void EventSystem::handleKeyReleasedEvents(const sf::Event &evt)
{
    if (evt.type != sf::Event::EventType::KeyReleased)
        return;
    if (evt.key.code == sf::Keyboard::Escape) {
        Game::getInstance().getWindow()->close();
        Game::getInstance().stop();
    }
}
} // namespace Game