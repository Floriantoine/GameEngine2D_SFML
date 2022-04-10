#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace components {

class RectangleShape : public fa::Component<RectangleShape> {
  public:
    RectangleShape()
    {
        this->_thickness = 1;
    };
    ~RectangleShape() = default;
    RectangleShape(float thickness) : _thickness(thickness)
    {
    }

    sf::RectangleShape _shape;
    float _thickness;
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components