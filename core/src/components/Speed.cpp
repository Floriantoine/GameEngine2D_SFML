#include "components/Speed.hpp"
#include "Game.hpp"

namespace components {
Speed::Speed(nlohmann::json config)
{
    if (config && config.type() == nlohmann::json::value_t::number_unsigned) {
        _speed = config;
    } else if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr) {
            if (config["init"].type() ==
                nlohmann::json::value_t::number_unsigned) {
                _speed = config["init"];
            }
        }
        if (config["rangeMin"] != nullptr) {
            _rangeMin = config["rangeMin"];
        }
        if (config["rangeMax"] != nullptr) {
            _rangeMax = config["rangeMax"];
        }
    }
    _initSpeed = _speed;
}

void Speed::factory(id_t entityId, nlohmann::json config)
{
    float speed = 0;
    float rangeMin = 0;
    float rangeMax = 0;

    if (config != nullptr &&
        config.type() == nlohmann::json::value_t::number_unsigned) {
        speed = config;
    } else if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr) {
            if (config["init"].type() ==
                nlohmann::json::value_t::number_unsigned) {
                speed = config["init"];
            }
        }
        if (config["rangeMin"] != nullptr) {
            rangeMin = config["rangeMin"];
        }
        if (config["rangeMax"] != nullptr) {
            rangeMax = config["rangeMax"];
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Speed>(entityId, speed, rangeMin, rangeMax);
}
void Speed::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("SpeedComponent")) {
        ImGui::InputFloat("CurrentSpeed##ImGuiComponentModifier", &_speed);
        ImGui::InputFloat("initSpeed##ImGuiComponentModifier", &_initSpeed);
        ImGui::SliderFloat(
            "rangeMin##ImGuiComponentModifier", &_rangeMin, 0, 100);
        ImGui::SliderFloat(
            "rangeMax##ImGuiComponentModifier", &_rangeMax, 0, 100);
    }
};
} // namespace components
