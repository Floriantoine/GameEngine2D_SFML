#pragma once

#include "component/Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class SolidBlock : public rtype::Component<SolidBlock> {
  public:
    bool _haveCollision;
    int _targetId;

    SolidBlock() : _haveCollision(false){};
    ~SolidBlock() = default;
};
} // namespace components