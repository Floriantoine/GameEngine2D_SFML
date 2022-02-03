#pragma once

#include "component/Component.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace components {

class RectangleShape : public rtype::Component<RectangleShape> {
  public:
    RectangleShape()
    {
        this->_size = sf::Vector2f(10, 10);
        this->_thickness = 1;
    };
    ~RectangleShape() = default;

    sf::RectangleShape _shape;
    sf::Vector2f _size;
    sf::Color _color;
    float _thickness;
};
} // namespace components