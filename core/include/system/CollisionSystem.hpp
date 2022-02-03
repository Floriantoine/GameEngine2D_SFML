#pragma once

#include "ASystem.hpp"
#include "Components.hpp"

namespace systems {

class CollisionSystem : public rtype::ASystem {
  public:
    long _elapsedtime = 0;
    CollisionSystem() : ASystem(){};
    ~CollisionSystem() = default;

    void update(long elapsedTime) override;
};
} // namespace systems