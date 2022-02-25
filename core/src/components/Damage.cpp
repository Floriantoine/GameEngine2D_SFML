
#include "components/Damage.hpp"
#include "Game.hpp"

namespace components {
void Damage::factory(id_t entityId, nlohmann::json config)
{
    int damage = 0;

    if (config != nullptr)
        damage = config;
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Damage>(entityId, damage);
}
void Damage::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("DamageComponent##ImguiModifier")) {
        ImGui::InputInt("Damage##DamageComponentModifier", &_damage);
    }
};
} // namespace components