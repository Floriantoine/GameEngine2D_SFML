#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "tools/random.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

namespace systems {

class GravitySystem : public rtype::ASystem {
  private:
    sf::VertexArray *_vertexArray;

    float delta_t = 0.2;
    int _vertexSize;

    void ExplicitEuler(int N, std::vector<sf::Vector2f> *cur_S,
        std::vector<sf::Vector2f> prior_S, std::vector<sf::Vector2f> S_derivs,
        float delta_t);

  public:
    GravitySystem(sf::VertexArray *vertexArray)
        : _vertexArray(vertexArray), _vertexSize(-1), ASystem(){};
    ~GravitySystem() = default;

    void update(long elapsedTime) override;
};
}