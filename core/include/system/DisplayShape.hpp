#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include <vector>

namespace systems {

class DisplayShape : public rtype::ASystem {
  public:
    DisplayShape() : ASystem(){};
    ~DisplayShape() = default;

    void update(long elapsedTime) override;
};
} // namespace systems