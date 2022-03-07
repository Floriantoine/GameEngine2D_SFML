#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics/Color.hpp>

namespace components {

class Color : public fa::Component<Color> {
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
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components