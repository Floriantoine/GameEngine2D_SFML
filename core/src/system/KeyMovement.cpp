#include "system/KeyMovement.hpp"
#include "Game.hpp"

namespace systems {

KeyMovement::KeyMovement() : ASystem()
{
    _observers = Observer{
        [&](KeyPressed const &event) {
            if (event.key == sf::Keyboard::Left) {
                this->_direction = std::string("Left");
            }
            if (event.key == sf::Keyboard::Right) {
                this->_direction = std::string("Right");
            }
            if (event.key == sf::Keyboard::Up) {
                this->_direction = std::string("Up");
            }
            if (event.key == sf::Keyboard::Down) {
                this->_direction = std::string("Down");
            }
        },
    };
    Game::Game::getInstance().getObserverManager().addObserver(&_observers);
};

void KeyMovement::update(long elapsedTime)
{
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 200) {
        if (this->_direction != "") {
            this->_elapsedTime = 0;
            auto array = this->componentManager_
                             ->getComponentList<components::KeyMovement>();
            for (auto it = array.begin(); it != array.end(); ++it) {
                components::SpawnPos *PosC =
                    this->componentManager_->getComponent<components::SpawnPos>(
                        it->first);
                if (!PosC)
                    return;
                if (this->_direction == "Left") {
                    PosC->_initPos.x -= 20;
                }
                if (this->_direction == "Right") {
                    PosC->_initPos.x += 20;
                }
                if (this->_direction == "Up") {
                    PosC->_initPos.y -= 20;
                }
                if (this->_direction == "Down") {
                    PosC->_initPos.y += 20;
                }
            }
            this->_direction = "";
        }
    }
};

} // namespace systems
