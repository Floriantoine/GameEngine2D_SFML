#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class Orbit : public rtype::Component<Orbit> {
  public:
    float _angle = 0;
    int _radius = 1;
    sf::Vector2f _pivotPoint{0, 0};

  public:
    Orbit() = default;
    Orbit(int radius, sf::Vector2f pivotPoint)
        : _radius(radius), _pivotPoint(pivotPoint){};
    ~Orbit() = default;
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components