#pragma once

#include "../components/HealthComponent.hpp"
#include "ASystem.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class PointParticleAlphaSystem : public rtype::ASystem {
  private:
    sf::VertexArray *_vertexArray;

  public:
    PointParticleAlphaSystem(sf::VertexArray *vertexArray)
        : _vertexArray(vertexArray), ASystem(){};
    ~PointParticleAlphaSystem() = default;

    void update(long elapsedTime) override
    {
        int count = _vertexArray->getVertexCount();

        for (int i = 0; i < count; i++) {
            components::HealthComponent *compLife =
                this->_componentManager
                    ->getComponent<components::HealthComponent>(i);
            if (compLife) {
                (*_vertexArray)[i].color.a -= std::max(
                    (int)((255 / compLife->_initHealth) * elapsedTime), 1);
                if ((*_vertexArray)[i].color.a < 0)
                    (*_vertexArray)[i].color.a = 0;
            }
        }
    }
};