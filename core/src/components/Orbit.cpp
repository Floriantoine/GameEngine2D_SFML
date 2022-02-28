
#include "components/systemActivator/Orbit.hpp"
#include "Game.hpp"

namespace components {
void Orbit::factory(id_t entityId, nlohmann::json config)
{
    int radius = 1;
    sf::Vector2f pivotPoint{0, 0};

    if (config.type() == nlohmann::json::value_t::number_unsigned) {
        radius = config;
        components::PosComponent *PosC =
            Game::Game::getInstance()
                .getComponentManager()
                .getComponent<components::PosComponent>(entityId);
        if (PosC) {
            pivotPoint = PosC->_pos;
        }
    }
    if (config.type() == nlohmann::json::value_t::object) {
        if (config["radius"] != nullptr) {
            radius = config["radius"];
        }
        if (config["pivotPoint"] != nullptr &&
            config.type() == nlohmann::json::value_t::object) {
            pivotPoint.x = config["pivotPoint"][0];
            pivotPoint.y = config["pivotPoint"][1];
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Orbit>(entityId, radius, pivotPoint);
}
void Orbit::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("OrbitComponent##ImGuiModifier")) {
    }
};
} // namespace components