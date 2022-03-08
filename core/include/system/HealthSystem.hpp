#pragma once

#include "ASystem.hpp"

namespace systems {

class HealthSystem : public fa::ASystem {
  public:
    long _elapsedTime = 0;
    HealthSystem() : ASystem(){};
    ~HealthSystem() = default;

    void update(long elapsedTime) override;
};
} // namespace systems
