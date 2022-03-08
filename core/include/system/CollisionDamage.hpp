#pragma once

#include "ASystem.hpp"

namespace systems {

class CollisionDamage : public fa::ASystem {
  public:
    CollisionDamage() : ASystem(){};
    ~CollisionDamage() = default;

    void update(long elapsedTime) override;
};
} // namespace system