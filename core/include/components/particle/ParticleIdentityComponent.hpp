#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class ParticleIdentity : public rtype::Component<ParticleIdentity> {
  public:
    ParticleIdentity(){};
};
} // namespace components