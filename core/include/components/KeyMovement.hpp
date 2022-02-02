#pragma once

#include "component/Component.hpp"

namespace components {

class KeyMovement : public rtype::Component<KeyMovement> {
  public:
    KeyMovement() = default;
    ~KeyMovement() = default;
};
} // namespace components