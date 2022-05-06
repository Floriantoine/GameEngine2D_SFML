#pragma once

#include "ASystem.hpp"

namespace systems {

class BehaviorSystem : public fa::ASystem {
  public:
    BehaviorSystem() : ASystem(){};
    ~BehaviorSystem() = default;

    void update(long elapsedTime) override;
};
} // namespace system