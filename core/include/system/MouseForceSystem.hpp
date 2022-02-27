
#pragma once

#include "ASystem.hpp"
#include "components/ForceComponent.hpp"
#include "observer/Observer.hpp"
#include "observer/ObserverManager.hpp"
#include "tools/random.hpp"

namespace rtype {

class MouseForceSystem : public ASystem {
  public:
    Observer _observers;
    ObserverManager &_observerManager;
    sf::Vector2i _mousePos{0, 0};
    sf::Vector2f _mouseVector{0, 0};
    long _elapsedTime = 0;

    MouseForceSystem(ObserverManager &observerManager)
        : ASystem(), _observerManager(observerManager)
    {
        _observers = Observer{
            [&](MouseMove const &mouse) {
                _mouseVector =
                    sf::Vector2f(_mousePos.x - mouse.x, _mousePos.y - mouse.y);
                _mousePos = sf::Vector2i(mouse.x, mouse.y);
            },
        };

        observerManager.addObserver(&_observers);
    };
    ~MouseForceSystem()
    {
        _observerManager.deleteObserver(&_observers);
    };

    void update(long elapsedTime) override
    {
        this->_elapsedTime += elapsedTime;
        if (this->_elapsedTime >= 16) {
            float speedX = tools::generate_random_number(
                _mouseVector.x - 1, _mouseVector.x + 1);
            float speedY = tools::generate_random_number(
                _mouseVector.y - 1, _mouseVector.y + 1);

            auto array = this->_componentManager
                             ->getComponentList<components::MouseForce>();
            for (auto &it: array) {
                components::MouseForce *mouseForceC =
                    static_cast<components::MouseForce *>(it.second);
                if (mouseForceC == nullptr)
                    continue;

                components::ForceComponent *forceC =
                    this->_componentManager
                        ->getComponent<components::ForceComponent>(it.first);

                forceC->_initForce = sf::Vector2f(-speedX, -speedY);
                _mouseVector = sf::Vector2f(0, 0);
            }
            this->_elapsedTime = 0;
        }
    };
};
} // namespace rtype
