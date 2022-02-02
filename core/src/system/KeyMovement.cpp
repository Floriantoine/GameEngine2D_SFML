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
                components::PosComponent *PosC =
                    this->componentManager_
                        ->getComponent<components::PosComponent>(it->first);
                if (this->_direction == "Left") {
                    std::cout << "init Pos: " << PosC->_initPos.x << std::endl;
                    PosC->_initPos.x -= 20;
                    std::cout << "after Pos: " << PosC->_initPos.x << std::endl;
                }
                if (this->_direction == "Right") {
                    PosC->_initPos.x += 20;
                }
            }
            this->_direction = "";
        }
    }
};

} // namespace systems
