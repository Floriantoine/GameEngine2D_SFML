#pragma once

#include "ASystem.hpp"
#include "Components.hpp"

namespace systems {

class OrbitSystem : public rtype::ASystem {
  public:
    long _elapsedTime = 0;

    OrbitSystem() : ASystem(){};
    ~OrbitSystem() = default;
    void update(long elapsedTime) override;
};
} // namespace system