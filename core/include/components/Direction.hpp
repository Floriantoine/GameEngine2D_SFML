#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace directions {

sf::Vector2i const UP_LEFT = sf::Vector2i(-1, -1);
sf::Vector2i const UP = sf::Vector2i(0, -1);
sf::Vector2i const UP_RIGHT = sf::Vector2i(1, -1);
sf::Vector2i const LEFT = sf::Vector2i(-1, 0);
sf::Vector2i const STATIC = sf::Vector2i(0, 0);
sf::Vector2i const RIGHT = sf::Vector2i(1, 0);
sf::Vector2i const DOWN_LEFT = sf::Vector2i(-1, 1);
sf::Vector2i const DOWN = sf::Vector2i(0, 1);
sf::Vector2i const DOWN_RIGHT = sf::Vector2i(1, 1);

enum class DirectionsInt : int
{
    UP_LEFT = 0,
    UP,
    UP_RIGHT,
    LEFT,
    STATIC,
    RIGHT,
    DOWN_LEFT,
    DOWN,
    DOWN_RIGHT
};
}; // namespace directions

namespace components {

class Direction : public fa::Component<Direction> {
  public:
    sf::Vector2i _direction;
    bool _continuous = false;

    Direction(sf::Vector2i direction, bool continuous)
        : _direction(direction), _continuous(continuous)
    {
    }
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components