
#include "components/BehaviorComponent.hpp"
#include "Game.hpp"

namespace components {
void BehaviorComponent::factory(fa::id_t entityId, nlohmann::json config)
{
    fa::behavior::Behavior behavior;

    if (config.type() == nlohmann::json::value_t::string) {
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::BehaviorComponent>(entityId, behavior);
}

void BehaviorComponent::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("BehaviorComponent##ImGuiModifier")) {
        if (ImGui::BeginChild("BehaviorComponentChild##ImGuiModifier")) {
            ImGui::EndChild();
        }
    }
};
} // namespace components