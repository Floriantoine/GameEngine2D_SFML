
#pragma once

#include "../components/PosComponent.hpp"
#include "ASystem.hpp"
#include "observer/Observer.hpp"
#include "observer/ObserverManager.hpp"

#include "tools/random.hpp"

namespace rtype {

class ParticleMousePosSystem : public ASystem {
  public:
    sf::Vector2f _mousePos{-100, -100};
    bool _haveMove = false;
    Observer _observers;
    ObserverManager &_observerManager;

    ParticleMousePosSystem(ObserverManager &observerManager)
        : ASystem(), _observerManager(observerManager)
    {
        _observers = Observer{
            [&](MouseMove const &mouse) {
                _mousePos = sf::Vector2f(mouse.x, mouse.y);
                this->_haveMove = true;
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
        if (this->_haveMove) {
            this->_haveMove = false;
            this->componentManager_->apply<components::PosComponent>(
                [&](components::PosComponent *component) {
                    component->_initPos = _mousePos;
                });
        }
    };
};
} // namespace rtype
