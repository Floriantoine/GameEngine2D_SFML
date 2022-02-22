
#include "components/RectangleShape.hpp"
#include "Game.hpp"

namespace components {
void RectangleShape::factory(id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::RectangleShape>(entityId);
}
} // namespace components