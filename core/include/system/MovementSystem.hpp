#pragma once

#include "ASystem.hpp"

namespace systems {

class MovementSystem : public fa::ASystem {
  public:
    MovementSystem() = default;
    ~MovementSystem() = default;

    void update(long elapsedTime) override;

  private:
    long _elapsedTime = 0;
};
} // namespace systems
