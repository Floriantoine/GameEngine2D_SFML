#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "tools/Chrono.hpp"
#include "tools/random.hpp"
#include <vector>

namespace systems {

class GravitySystem : public rtype::ASystem {
  private:
    float delta_t = 0.2;
    long _elapsedtime = 0;

    void ExplicitEuler(int N, std::vector<sf::Vector2f> *cur_S,
        std::vector<sf::Vector2f> prior_S, std::vector<sf::Vector2f> S_derivs,
        float delta_t);

  public:
    GravitySystem() : ASystem(){};
    ~GravitySystem() = default;

    void update(long elapsedTime) override;
};
} // namespace systems