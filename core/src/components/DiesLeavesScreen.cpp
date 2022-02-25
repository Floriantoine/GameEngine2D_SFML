
#include "components/DiesLeavesScreen.hpp"
#include "Game.hpp"

namespace components {
void DiesLeavesScreen::factory(id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::DiesLeavesScreen>(entityId);
}
void DiesLeavesScreen::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("DiesLeavesScreenComponent")) {
    }
};
} // namespace components