
#include "components/RectangleShape.hpp"
#include "Game.hpp"

namespace components {
void RectangleShape::factory(fa::id_t entityId, nlohmann::json config)
{
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::RectangleShape>(entityId);
}
void RectangleShape::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("RectangleShapeComponent")) {
    }
};
} // namespace components