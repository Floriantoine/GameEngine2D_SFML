
#include "components/MasseComponent.hpp"
#include "Game.hpp"

namespace components {
void MasseComponent::factory(id_t entityId, nlohmann::json config)
{
    int masse = 1;
    if (config.type() != nlohmann::json::value_t::object &&
        config.type() != nlohmann::json::value_t::array) {
        masse = config;
    }

    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::MasseComponent>(entityId, masse);
}
} // namespace components