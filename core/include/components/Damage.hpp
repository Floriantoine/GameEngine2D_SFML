#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class Damage : public rtype::Component<Damage> {
  public:
    int _damage;
    Damage() : _damage(1){};
    Damage(int damage) : _damage(damage)
    {
    }
    Damage(nlohmann::json config)
    {
        // To do
    }
};
} // namespace components