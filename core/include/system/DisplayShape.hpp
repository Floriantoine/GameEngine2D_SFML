#pragma once

#include "ASystem.hpp"
#include <vector>

namespace systems {

class DisplayShape : public fa::ASystem {
  public:
    DisplayShape() : ASystem(){};
    ~DisplayShape() = default;

    void update(long elapsedTime) override;
};
} // namespace systems