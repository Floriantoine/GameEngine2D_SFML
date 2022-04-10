
#include "components/DiesLeavesScreen.hpp"
#include "Game.hpp"

namespace components {
void DiesLeavesScreen::factory(fa::id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::DiesLeavesScreen>(entityId);
}
void DiesLeavesScreen::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("DiesLeavesScreenComponent##ImGuiModifier")) {
        if (ImGui::BeginChild(
                "DiesLeavesScreenComponentChild##ImGuiModifier")) {
            ImGui::Text("no Modifier");
            ImGui::EndChild();
        }
    }
};
} // namespace components