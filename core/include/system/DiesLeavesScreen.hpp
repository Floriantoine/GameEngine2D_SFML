#pragma once

#include "ASystem.hpp"

namespace systems {

class DiesLeavesScreen : public fa::ASystem {
  public:
    long _elapsedTime = 0;
    DiesLeavesScreen() : ASystem(){};
    ~DiesLeavesScreen() = default;

    void update(long elapsedTime) override;
};
} // namespace systems