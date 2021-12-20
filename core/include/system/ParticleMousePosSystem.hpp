
#pragma once

#include "../components/PosComponent.hpp"
#include "ASystem.hpp"
#include "observer/Observer.hpp"
#include "observer/ObserverManager.hpp"

#include "tools/random.hpp"

namespace rtype {

class ParticleMousePosSystem : public ASystem {
  public:
    sf::Vector2i _mousePos{-100, -100};
    Observer _observers;
    ObserverManager &_observerManager;

    ParticleMousePosSystem(ObserverManager &observerManager)
        : ASystem(), _observerManager(observerManager)
    {
        _observers = Observer{
            [&](MouseMove const &mouse) {
                _mousePos = sf::Vector2i(mouse.x, mouse.y);
            },
        };

        observerManager.addObserver(&_observers);
    };
    ~ParticleMousePosSystem()
    {
        _observerManager.deleteObserver(&_observers);
    };

    void update(long elapsedTime) override
    {
        this->componentManager_->apply<PosComponent>(
            [&](PosComponent *component) { component->_initPos = _mousePos; });
    };
};
} // namespace rtype
