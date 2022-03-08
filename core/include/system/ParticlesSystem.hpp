#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "tools/Chrono.hpp"
#include "tools/random.hpp"
#include <SFML/Graphics/VertexArray.hpp>

namespace systems {

class ParticlesSystem : public fa::ASystem {
  private:
    sf::VertexArray _vertexArray;
    long _elapsedTime;

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

    void reset(fa::id_t index);

  public:
    ParticlesSystem() : _vertexArray(sf::Points, 0), ASystem(){};
    ~ParticlesSystem() = default;

    void update(long elapsedTime) override;
};
} // namespace systems