#include "system/KeyMovement.hpp"
#include "Game.hpp"

namespace systems {

KeyMovement::KeyMovement() : ASystem()
{
    _observers = Observer{
        [&](KeyPressed const &event) {
            if (event.key == sf::Keyboard::Left) {
                this->_direction = std::string("Left");
                tools::Chrono::event("KeyMovement-Input");
            }
            if (event.key == sf::Keyboard::Right) {
                this->_direction = std::string("Right");
                tools::Chrono::event("KeyMovement-Input");
            }
            if (event.key == sf::Keyboard::Up) {
                this->_direction = std::string("Up");
                tools::Chrono::event("KeyMovement-Input");
            }
            if (event.key == sf::Keyboard::Down) {
                this->_direction = std::string("Down");
                tools::Chrono::event("KeyMovement-Input");
            }
        },
    };
    Game::Game::getInstance().getObserverManager().addObserver(&_observers);
};

void KeyMovement::update(long elapsedTime)
{
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        if (this->_direction != "") {
            auto array = this->_componentManager
                             ->getComponentList<components::KeyMovement>();
            for (auto &it: array) {
                components::PosComponent *PosC =
                    this->_componentManager
                        ->getComponent<components::PosComponent>(it.first);
                if (!PosC)
                    return;
                int step = 4 * _elapsedTime / 16;
                if (this->_direction == "Left") {
                    PosC->_pos.x -= step;
                } else if (this->_direction == "Right") {
                    PosC->_pos.x += step;
                } else if (this->_direction == "Up") {
                    PosC->_pos.y -= step;
                } else if (this->_direction == "Down") {
                    PosC->_pos.y += step;
                }
            }
            this->_direction = "";
        }
        this->_elapsedTime = 0;
    }
};

} // namespace systems
