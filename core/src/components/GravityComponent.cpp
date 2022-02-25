
#include "components/GravityComponent.hpp"
#include "Game.hpp"

namespace components {
void Gravity::factory(id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Gravity>(entityId);
}
void Gravity::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("GravityComponent")) {
    }
};
} // namespace components