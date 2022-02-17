#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>

namespace components {

class Size : public rtype::Component<Size> {
  public:
    sf::Vector2f _size = sf::Vector2f(1, 1);
    sf::Vector2f _initSize = sf::Vector2f(1, 1);
    sf::Vector2f _rangeMin = sf::Vector2f(0, 0);
    sf::Vector2f _rangeMax = sf::Vector2f(0, 0);
    Size(sf::Vector2f size) : _size(size), _initSize(size)
    {
    }
    Size(nlohmann::json config);
};
} // namespace components