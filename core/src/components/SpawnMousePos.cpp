
#include "components/systemActivator/SpawnMousePos.hpp"
#include "Game.hpp"

namespace components {
void SpawnMousePos::factory(id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::SpawnMousePos>(entityId);
}
void SpawnMousePos::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("SpawnMousePosComponent")) {
    }
};
} // namespace components