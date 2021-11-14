#pragma once

#include "../component/Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace rtype {

class PosComponent : public Component<PosComponent> {
  public:
    sf::Vector2i pos{-100, -100};
    sf::Vector2i _initPos{-100, -100};

  public:
    PosComponent() = default;
    PosComponent(sf::Vector2i pos) : pos{pos}, _initPos{pos}
    {
    }
};
} // namespace rtype