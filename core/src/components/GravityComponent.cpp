
#include "components/GravityComponent.hpp"
#include "Game.hpp"

namespace components {
void Gravity::factory(id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Gravity>(entityId);
}
} // namespace components