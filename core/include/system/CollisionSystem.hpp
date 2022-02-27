#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "tools/Chrono.hpp"

namespace systems {

struct collisStruct
{
    sf::FloatRect _floatRect;
    int id;
    int *targetId;
    bool *_haveCollision;
};

class CollisionSystem : public rtype::ASystem {
  public:
    long _elapsedTime = 0;
    CollisionSystem() : ASystem(){};
    ~CollisionSystem() = default;

    void update(long elapsedTime) override;
};
} // namespace systems