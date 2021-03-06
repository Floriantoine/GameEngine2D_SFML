
#pragma once

#include "../components/ForceComponent.hpp"
#include "../components/HealthComponent.hpp"
#include "../components/PosComponent.hpp"
#include "ASystem.hpp"
#include "observer/Observer.hpp"
#include "observer/ObserverManager.hpp"
#include <SFML/Graphics/VertexArray.hpp>

namespace fa {

class ParticleMouseTargetSystem : public ASystem {
  public:
    sf::VertexArray *_vertexArray;
    Observer _observers;
    sf::Vector2i _mousePos{0, 0};
    ObserverManager &_observerManager;

    ParticleMouseTargetSystem(
        ObserverManager &observerManager, sf::VertexArray *vertexArray)
        : ASystem(), _observerManager(observerManager),
          _vertexArray(vertexArray)
    {
        _observers = Observer{
            [&](MouseMove const &mouse) {
                _mousePos = sf::Vector2i(mouse.x, mouse.y);
            },
        };

        observerManager.addObserver(&_observers);
    };
    ~ParticleMouseTargetSystem()
    {
        _observerManager.deleteObserver(&_observers);
    };

    void update(long elapsedTime) override
    {
        int count = _vertexArray->getVertexCount();

        for (int i = 0; i < count; i++) {
            components::ForceComponent *compForce =
                this->_componentManager
                    ->getComponent<components::ForceComponent>(i);
            components::HealthComponent *compLife =
                this->_componentManager
                    ->getComponent<components::HealthComponent>(i);
            components::PosComponent *compPos =
                this->_componentManager->getComponent<components::PosComponent>(
                    i);
            if (compLife != nullptr && compPos != nullptr &&
                compForce != nullptr) {
                if (((*_vertexArray)[i].position.x >= _mousePos.x - 2 &&
                        (*_vertexArray)[i].position.x <= _mousePos.x + 2) &&
                    ((*_vertexArray)[i].position.y >= _mousePos.y - 2 &&
                        (*_vertexArray)[i].position.y <= _mousePos.y + 2)) {
                    compLife->health = 0;
                } else {
                    compForce->force = sf::Vector2f(
                        -(((*_vertexArray)[i].position.x - _mousePos.x) /
                            compLife->health),
                        -(((*_vertexArray)[i].position.y - _mousePos.y) /
                            compLife->health));
                }
            }
        }
    };
};
} // namespace fa
