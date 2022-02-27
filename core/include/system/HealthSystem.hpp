#pragma once

#include "ASystem.hpp"
#include "Components.hpp"

namespace systems {

class HealthSystem : public rtype::ASystem {
  public:
    long _elapsedTime = 0;
    HealthSystem() : ASystem(){};
    ~HealthSystem() = default;

    void update(long elapsedTime) override;
};
} // namespace systems
