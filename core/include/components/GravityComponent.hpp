#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class Gravity : public fa::Component<Gravity> {
  public:
    sf::Vector2f _cur_S;

  public:
    Gravity() = default;
    ~Gravity() = default;
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components