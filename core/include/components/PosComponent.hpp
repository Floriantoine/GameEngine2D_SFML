#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class PosComponent : public fa::Component<PosComponent> {
  public:
    sf::Vector2f _pos{0, 0};

  public:
    PosComponent() = default;
    PosComponent(nlohmann::json config);
    PosComponent(sf::Vector2f pos) : _pos(pos)
    {
    }
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components