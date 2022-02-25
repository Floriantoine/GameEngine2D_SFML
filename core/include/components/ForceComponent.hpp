#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class ForceComponent : public rtype::Component<ForceComponent> {
  public:
    sf::Vector2f force{0, 0};
    sf::Vector2f _initForce{0, 0};
    sf::Vector2f _rangeMin{0, 0};
    sf::Vector2f _rangeMax{0, 0};

  public:
    ForceComponent() = default;
    ForceComponent(nlohmann::json config);
    ForceComponent(
        sf::Vector2f initForce, sf::Vector2f rangeMin, sf::Vector2f rangeMax);
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components