#include "system/KeyMovement.hpp"
#include "Game.hpp"
#include "components/Direction.hpp"
#include "components/KeyMovement.hpp"
#include "observer/ObserverManager.hpp"

namespace systems {

KeyMovement::KeyMovement() : ASystem()
{
    _observers = Observer{
        [&](KeyPressed const &event) {
            this->_direction = directions::STATIC;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                this->_direction += directions::LEFT;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                this->_direction += directions::RIGHT;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                this->_direction += directions::UP;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                this->_direction += directions::DOWN;
            }
        },
    };
    Game::Game::getInstance().getObserverManager().addObserver(&_observers);
};

void KeyMovement::update(long elapsedTime)
{
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        this->_direction = directions::STATIC;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            this->_direction += directions::LEFT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            this->_direction += directions::RIGHT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            this->_direction += directions::UP;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            this->_direction += directions::DOWN;
        }
        if (this->_direction != directions::STATIC) {
            auto array = this->_componentManager
                             ->getComponentList<components::KeyMovement>();
            for (auto &it: array) {
                components::Direction *directionC =
                    this->_componentManager
                        ->getComponent<components::Direction>(it.first);
                if (!directionC)
                    return;
                directionC->_direction = this->_direction;
            }
            this->_direction = directions::STATIC;
        }
        this->_elapsedTime = 0;
    }
};

} // namespace systems
