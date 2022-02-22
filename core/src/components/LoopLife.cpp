
#include "components/LoopLife.hpp"
#include "Game.hpp"

namespace components {
void LoopLife::factory(id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::LoopLife>(entityId);
}
} // namespace components