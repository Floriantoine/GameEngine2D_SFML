#pragma once

#include "component/Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class MouseForce : public rtype::Component<MouseForce> {
  public:
    MouseForce() = default;
};
} // namespace components