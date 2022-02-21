#include "components/HealthComponent.hpp"
#include "Game.hpp"

namespace components {
void HealthComponent::factory(id_t entityId, nlohmann::json config)
{
    int initHealth = 0;
    int rangeMin = 0;
    int rangeMax = 0;

    if (config["init"] != nullptr) {
        initHealth = config["init"];
    }
    if (config["rangeMin"] != nullptr) {
        rangeMin = config["rangeMin"];
    }
    if (config["rangeMax"] != nullptr) {
        rangeMax = config["rangeMax"];
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::HealthComponent>(
            entityId, initHealth, rangeMin, rangeMax);
}
} // namespace components