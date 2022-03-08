#include "components/TargetEntity.hpp"
#include "Game.hpp"
#include "tools/tools.hpp"

namespace components {
void TargetEntity::factory(id_t entityId, nlohmann::json config)
{
    id_t targetId = -1;

    if (config != nullptr) {
        if (config.type() == nlohmann::json::value_t::number_unsigned) {
            targetId = config;
        }
        if (config.type() == nlohmann::json::value_t::string) {
            targetId = tools::stringToId(config);
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::TargetEntity>(entityId, targetId);
}
void TargetEntity::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("TargetEntity##ImGuiModifier")) {
    }
};
} // namespace components