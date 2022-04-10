
#include "components/MasseComponent.hpp"
#include "Game.hpp"

namespace components {
void MasseComponent::factory(fa::id_t entityId, nlohmann::json config)
{
    int masse = 1;
    if (config != nullptr && config.type() != nlohmann::json::value_t::object &&
        config.type() != nlohmann::json::value_t::array) {
        masse = config;
    }

    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::MasseComponent>(entityId, masse);
}
void MasseComponent::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("Masse##ImGuiModifierECS")) {
        ImGui::InputInt("Masse##ImGuiModifierECSMasseComp", &this->masse);
    }
};
} // namespace components