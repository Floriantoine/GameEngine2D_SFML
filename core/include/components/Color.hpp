#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics/Color.hpp>

namespace components {

class Color : public rtype::Component<Color> {
  public:
    sf::Color _color;
    Color()
    {
        _color = sf::Color::White;
    };
    Color(sf::Color color) : _color(color)
    {
    }
    Color(nlohmann::json config)
    {
        _color = sf::Color::Red;
    }
};
} // namespace components