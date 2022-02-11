#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class Gravity : public rtype::Component<Gravity> {
  public:
    sf::Vector2f _cur_S;

  public:
    Gravity() = default;
};
} // namespace components