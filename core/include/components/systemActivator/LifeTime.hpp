#pragma once

#include "component/Component.hpp"

namespace components {

class LifeTime : public rtype::Component<LifeTime> {
  public:
    LifeTime() = default;
    ~LifeTime() = default;
};
} // namespace components