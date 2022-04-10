
#include "components/systemActivator/LinearMovement.hpp"
#include "Game.hpp"

namespace components {
void LinearMovement::factory(fa::id_t entityId, nlohmann::json config)
{
    std::string direction = "";
    if (config != nullptr) {
        direction = config;
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::LinearMovement>(entityId, direction);
}
void LinearMovement::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader(
            "LinearMovementComponent##LinearMovementImGuiModifier")) {
    }
};
} // namespace components