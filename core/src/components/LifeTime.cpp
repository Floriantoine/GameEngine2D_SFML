
#include "Game.hpp"
#include "components/systemActivator/LifeTime.hpp"

namespace components {
void LifeTime::factory(id_t entityId, nlohmann::json config)
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
}