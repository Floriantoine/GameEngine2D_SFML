
#pragma once

#include "../components/ForceComponent.hpp"
#include "../observer/Observer.hpp"
#include "../observer/ObserverManager.hpp"
#include "./ASystem.hpp"
#include "tools/random.hpp"

namespace rtype {

class ParticleMouseForceSystem : public ASystem {
  public:
    Observer _observers;
    sf::Vector2i _mousePos{0, 0};
    ObserverManager &_observerManager;
    sf::Vector2f _mouseVector{0, 0};

    ParticleMouseForceSystem(ObserverManager &observerManager)
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
    ~ParticleMouseForceSystem()
    {
        _observerManager.deleteObserver(&_observers);
    };

    void update(long elapsedTime) override
    {
        float speedX = tools::generate_random_number(
            _mouseVector.x - 1, _mouseVector.x + 1);
        float speedY = tools::generate_random_number(
            _mouseVector.y - 1, _mouseVector.y + 1);

        this->componentManager_->apply<ForceComponent>(
            [&](ForceComponent *component) {
                component->_initForce = sf::Vector2f(-speedX, -speedY);
            });
    };
};
} // namespace rtype
