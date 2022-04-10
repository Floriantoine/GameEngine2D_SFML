
#include "components/KeyMovement.hpp"
#include "Game.hpp"

namespace components {
void KeyMovement::factory(fa::id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::KeyMovement>(entityId);
}
void KeyMovement::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("KeyMovementComponent")) {
    }
};
} // namespace components