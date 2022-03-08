
#include "Game.hpp"
#include "components/SolidBlock.hpp"

namespace components {
void SolidBlock::factory(fa::id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::SolidBlock>(entityId);
}
void SolidBlock::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("SolidBlockComponent")) {
    }
};
}