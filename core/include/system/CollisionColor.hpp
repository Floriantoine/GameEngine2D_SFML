#pragma once

#include "ASystem.hpp"
#include "Components.hpp"

namespace systems {

class CollisionColor : public fa::ASystem {
  public:
    CollisionColor() : ASystem(){};
    ~CollisionColor() = default;

    void update(long elapsedTime) override;
};
} // namespace system