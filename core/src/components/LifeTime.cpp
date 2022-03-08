
#include "components/systemActivator/LifeTime.hpp"
#include "Game.hpp"

namespace components {
void LifeTime::factory(fa::id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::LifeTime>(entityId);
}
void LifeTime::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("LifeTimeComponent")) {
    }
};
} // namespace components