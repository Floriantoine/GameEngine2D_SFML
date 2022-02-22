
#include "components/MouseForce.hpp"
#include "Game.hpp"

namespace components {
void MouseForce::factory(id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::MouseForce>(entityId);
}
} // namespace components