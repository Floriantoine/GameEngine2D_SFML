
#include "components/ParentRef.hpp"
#include "Game.hpp"

namespace components {
void ParentRef::factory(fa::id_t entityId, nlohmann::json config)
{
    int parentRef = -1;

    if (config.type() == nlohmann::json::value_t::number_unsigned) {
        parentRef = config;
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::ParentRef>(entityId, parentRef);
}
void ParentRef::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("ParentRef##ImGuiModifier")) {
    }
};
} // namespace components