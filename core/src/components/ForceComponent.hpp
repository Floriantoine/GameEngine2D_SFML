#pragma once

#include "../component/Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace rtype {

class ForceComponent : public Component<ForceComponent> {
  public:
    sf::Vector2f force{0, 0};
    sf::Vector2f _initForce{0, 0};

  public:
    ForceComponent() = default;
    ForceComponent(sf::Vector2f force) : force{force}, _initForce{force}
    {
    }
};
} // namespace rtype