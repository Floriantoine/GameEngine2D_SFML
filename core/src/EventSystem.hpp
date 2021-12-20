/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Event System
*/

#pragma once

#include "observer/ObserverManager.hpp"
#include "observer/Subject.hpp"
#include <SFML/Window/Event.hpp>

namespace Game {

class EventSystem {
  public:
    void update(long elapsedTime);
    void handleCloseEvent(const sf::Event &evt);
    void handleMouseMove(const sf::Event &evt);
    void handleMouseButtonPressedEvents(const sf::Event &evt);
    void handleMouseButtonReleasedEvents(const sf::Event &evt);
    void handleKeyPressedEvents(const sf::Event &evt);
    void handleKeyReleasedEvents(const sf::Event &evt);
    Subject _subject;
    EventSystem(ObserverManager &observerManager);
};

} // namespace Game
