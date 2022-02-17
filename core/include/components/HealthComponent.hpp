#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class HealthComponent : public rtype::Component<HealthComponent> {
  public:
    int health{0};
    int _initHealth{0};
    int _rangeMin{0};
    int _rangeMax{0};

  public:
    HealthComponent() = default;
    HealthComponent(int inputHealth) : health(inputHealth)
    {
    }
    HealthComponent(nlohmann::json config)
    {
        if (config["init"] != nullptr) {
            _initHealth = config["init"];
            health = _initHealth;
        }
        if (config["rangeMin"] != nullptr) {
            _rangeMin = config["rangeMin"];
        }
        if (config["rangeMax"] != nullptr) {
            _rangeMax = config["rangeMax"];
        }
    }
};
} // namespace components