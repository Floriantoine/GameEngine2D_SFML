
#include "components/Color.hpp"
#include "Game.hpp"
#include <math.h>

namespace components {
void Color::factory(fa::id_t entityId, nlohmann::json config)
{
    sf::Color color = sf::Color::White;

    if (config.type() == nlohmann::json::value_t::string) {
        if (config == "red") {
            color = sf::Color::Red;
        }
        if (config == "blue") {
            color = sf::Color::Blue;
        }
        if (config == "green") {
            color = sf::Color::Green;
        }
    } else if (config.type() == nlohmann::json::value_t::object) {
        if (config["r"] != nullptr &&
            config["r"].type() != nlohmann::json::value_t::number_integer) {
            color.r = config["r"];
        }
        if (config["g"] != nullptr &&
            config["g"].type() != nlohmann::json::value_t::number_integer) {
            color.g = config["g"];
        }
        if (config["b"] != nullptr &&
            config["b"].type() != nlohmann::json::value_t::number_integer) {
            color.b = config["b"];
        }
        if (config["a"] != nullptr &&
            config["a"].type() != nlohmann::json::value_t::number_integer) {
            color.r = config["a"];
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Color>(entityId, color);
}
void Color::dislayImGuiPanel()
{
    static ImVec4 array = ImVec4(_color.r / 255.0f, _color.g / 255.0f,
        _color.b / 255.0f, _color.a / 255.0f);
    if (ImGui::CollapsingHeader("ColorComponent##ImGuiModifier")) {
        if (ImGui::BeginChild("ColorComponentChild##ImGuiModifier")) {
            if (ImGui::ColorPicker4(
                    "Color Picker##ColorImGuiModifier", (float *)&array)) {
                _color.r = (sf::Uint8)round(array.x * 255);
                _color.g = (sf::Uint8)round(array.y * 255);
                _color.b = (sf::Uint8)round(array.z * 255);
                _color.a = (sf::Uint8)round(array.w * 255);
            }
            ImGui::EndChild();
        }
    }
};
} // namespace components