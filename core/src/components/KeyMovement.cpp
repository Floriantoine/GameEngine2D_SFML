
#include "components/KeyMovement.hpp"
#include "Game.hpp"

namespace components {
void KeyMovement::factory(id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::KeyMovement>(entityId);
}
} // namespace components