#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

namespace components {

class ParticleIdentity : public fa::Component<ParticleIdentity> {
  public:
    sf::PrimitiveType _type = sf::PrimitiveType::Points;
    bool _isInit = false;
    ParticleIdentity() = default;
    ParticleIdentity(sf::PrimitiveType type) : _type(type){};
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components