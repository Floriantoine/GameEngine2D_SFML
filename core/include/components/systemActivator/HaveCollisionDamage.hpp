#pragma once

#include "component/Component.hpp"

namespace components {

class HaveCollisionDamage : public rtype::Component<HaveCollisionDamage> {
  public:
    HaveCollisionDamage() = default;
    ~HaveCollisionDamage() = default;
};
} // namespace components