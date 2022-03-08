
#include "components/LoopLife.hpp"
#include "Game.hpp"

namespace components {
void LoopLife::factory(fa::id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::LoopLife>(entityId);
}
void LoopLife::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("LoopLifeComponent")) {
    }
};
} // namespace components