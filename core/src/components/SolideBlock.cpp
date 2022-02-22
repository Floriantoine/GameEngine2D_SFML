
#include "Game.hpp"
#include "components/SolidBlock.hpp"

namespace components {
void SolidBlock::factory(id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::SolidBlock>(entityId);
}
}