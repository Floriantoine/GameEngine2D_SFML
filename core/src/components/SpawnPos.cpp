
#include "Game.hpp"
#include "components/SpawnPosComponent.hpp"

namespace components {
void SpawnPos::factory(fa::id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::SpawnPos>(entityId);
}
void SpawnPos::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("SpawnPosComponent")) {
    }
};
} // namespace components