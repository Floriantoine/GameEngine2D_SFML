#pragma once

#include "ASystem.hpp"
#include "Components.hpp"

namespace systems {

class MovementSystem : public rtype::ASystem {
  public:
    MovementSystem() = default;
    ~MovementSystem() = default;

    void update(long elapsedTime) override;

  private:
    long _elapsedTime = 0;
};
} // namespace systems
