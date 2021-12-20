#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "tools/random.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class PointParticleGravitySystem : public rtype::ASystem {
  private:
    sf::VertexArray *_vertexArray;

    std::vector<sf::Vector2f> cur_S;
    std::vector<sf::Vector2f> prior_S;
    std::vector<sf::Vector2f> S_derivs;
    float delta_t = 0.2;
    int _vertexSize;

    void ExplicitEuler(int N, std::vector<sf::Vector2f> prior_S,
        std::vector<sf::Vector2f> S_derivs, float delta_t);

  public:
    PointParticleGravitySystem(sf::VertexArray *vertexArray)
        : _vertexArray(vertexArray), cur_S(1), prior_S(1), S_derivs(1),
          _vertexSize(-1), ASystem(){};
    ~PointParticleGravitySystem() = default;

    void init();

    template <class T>
    void generateProprietyRange(T *value, T initValue, T rangeMin, T rangeMax)
    {
        (*value) = tools::generate_random_number(
            initValue - rangeMin, initValue + rangeMax);
    }

    template <class T>
    void generateVectorProprietyRange(
        T *value, T initValue, T rangeMin, T rangeMax)
    {
        (*value).x = tools::generate_random_number(
            initValue.x - rangeMin.x, initValue.x + rangeMax.x);
        (*value).y = tools::generate_random_number(
            initValue.y - rangeMin.y, initValue.y + rangeMax.y);
    }

    void resetParticle(int index);

    void update(long elapsedTime) override;
};