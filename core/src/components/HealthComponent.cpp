#include "components/HealthComponent.hpp"
#include "Game.hpp"

namespace components {
void HealthComponent::factory(id_t entityId, nlohmann::json config)
{
    int initHealth = 0;
    int rangeMin = 0;
    int rangeMax = 0;

    if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr) {
            initHealth = config["init"];
        }
        if (config["rangeMin"] != nullptr) {
            rangeMin = config["rangeMin"];
        }
        if (config["rangeMax"] != nullptr) {
            rangeMax = config["rangeMax"];
        }
    } else if (config.type() == nlohmann::json::value_t::number_unsigned) {
        initHealth = config;
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::HealthComponent>(
            entityId, initHealth, rangeMin, rangeMax);
}
void HealthComponent::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("HealthComponent")) {
        ImGui::InputInt(
            "Health##ImGuiHealthComponentModifier", &this->_initHealth);
        ImGui::SliderInt(
            "rangeMin##ImGuiHealthComponentModifier", &this->_rangeMin, 0, 100);
        ImGui::SliderInt(
            "rangeMax##ImGuiHealthComponentModifier", &this->_rangeMax, 0, 100);
    }
};
} // namespace components