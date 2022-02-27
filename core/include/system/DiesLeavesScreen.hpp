#pragma once

#include "ASystem.hpp"
#include "Components.hpp"

namespace systems {

class DiesLeavesScreen : public rtype::ASystem {
  public:
    long _elapsedTime = 0;
    DiesLeavesScreen() : ASystem(){};
    ~DiesLeavesScreen() = default;

    void update(long elapsedTime) override;
};
} // namespace systems