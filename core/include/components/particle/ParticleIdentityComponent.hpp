#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class ParticleIdentity : public rtype::Component<ParticleIdentity> {
  public:
    sf::PrimitiveType _type = sf::PrimitiveType::Points;
    bool _isInit = false;
    ParticleIdentity() = default;
    ParticleIdentity(sf::PrimitiveType type) : _type(type){};
};
} // namespace components