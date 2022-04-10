#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
namespace components {

class HealthComponent : public fa::Component<HealthComponent> {
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
    HealthComponent(int initHealth, int rangeMin, int rangeMax)
        : _initHealth(initHealth), _rangeMin(rangeMin), _rangeMax(rangeMax),
          health(initHealth)
    {
    }
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components