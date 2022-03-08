
#include "components/systemActivator/HaveCollisionDamage.hpp"
#include "Game.hpp"

namespace components {
void HaveCollisionDamage::factory(fa::id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::HaveCollisionDamage>(entityId);
}
void HaveCollisionDamage::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("HaveCollisionDamage##ImGuiModifier")) {
    }
};
} // namespace components