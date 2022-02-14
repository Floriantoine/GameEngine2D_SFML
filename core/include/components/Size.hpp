#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class Size : public rtype::Component<Size> {
  public:
    sf::Vector2f _size;
    Size(sf::Vector2f size) : _size(size)
    {
    }
    Size(nlohmann::json config)
    {
        _size = sf::Vector2f(10, 10);
    }
};
} // namespace components