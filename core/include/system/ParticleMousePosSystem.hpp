
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
    long _elapsedTime;

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
        _elapsedTime += elapsedTime;
        if (_elapsedTime < 16) {
            return;
        }
        _elapsedTime = 0;
        if (this->_haveMove) {
            this->_haveMove = false;
            auto array = this->componentManager_
                             ->getComponentList<components::SpawnMousePos>();
            for (auto &it: array) {
                components::SpawnPos *spawnPos =
                    this->componentManager_->getComponent<components::SpawnPos>(
                        it.first);
                if (spawnPos) {
                    spawnPos->_initPos = _mousePos;
                }
            }
        }
    };
};
} // namespace rtype
