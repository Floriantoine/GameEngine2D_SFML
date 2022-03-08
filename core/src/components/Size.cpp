#include "components/Size.hpp"
#include "Game.hpp"

namespace components {
Size::Size(nlohmann::json config)
{
    if (config.type() == nlohmann::json::value_t::array &&
        config[0] != nullptr && config[1] != nullptr) {
        _size = sf::Vector2f(config[0], config[1]);
    } else if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr) {
            if (config["init"].type() == nlohmann::json::value_t::array &&
                config["init"].size() == 2) {
                _size = sf::Vector2f(config["init"][0], config["init"][1]);
            } else {
                _size = sf::Vector2f(config["init"], config["init"]);
            }
        }
        if (config["rangeMin"] != nullptr && config["rangeMin"].size() == 2) {
            _rangeMin =
                sf::Vector2f(config["rangeMin"][0], config["rangeMin"][1]);
        }
        if (config["rangeMax"] != nullptr && config["rangeMax"].size() == 2) {
            _rangeMax =
                sf::Vector2f(config["rangeMax"][0], config["rangeMax"][1]);
        }
    } else {
        _size = sf::Vector2f(config, config);
    }
    _initSize = _size;
}

void Size::factory(fa::id_t entityId, nlohmann::json config)
{
    sf::Vector2f size = {0, 0};
    sf::Vector2f rangeMin = {0, 0};
    sf::Vector2f rangeMax = {0, 0};

    if (config.type() == nlohmann::json::value_t::array &&
        config[0] != nullptr && config[1] != nullptr) {
        size = sf::Vector2f(config[0], config[1]);
    } else if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr) {
            if (config["init"].type() == nlohmann::json::value_t::array &&
                config["init"].size() == 2) {
                size = sf::Vector2f(config["init"][0], config["init"][1]);
            } else {
                size = sf::Vector2f(config["init"], config["init"]);
            }
        }
        if (config["rangeMin"] != nullptr && config["rangeMin"].size() == 2) {
            rangeMin =
                sf::Vector2f(config["rangeMin"][0], config["rangeMin"][1]);
        }
        if (config["rangeMax"] != nullptr && config["rangeMax"].size() == 2) {
            rangeMax =
                sf::Vector2f(config["rangeMax"][0], config["rangeMax"][1]);
        }
    } else {
        size = sf::Vector2f(config, config);
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Size>(entityId, size, rangeMin, rangeMax);
}
void Size::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("SizeComponent")) {
        ImGui::InputFloat2("CurrentSize##ImGuiComponentModifier", &_size.x);
        ImGui::InputFloat2("initSize##ImGuiComponentModifier", &_initSize.x);
        ImGui::SliderFloat2(
            "rangeMin##ImGuiComponentModifier", &_rangeMin.x, 0, 100);
        ImGui::SliderFloat2(
            "rangeMax##ImGuiComponentModifier", &_rangeMax.x, 0, 100);
    }
};
} // namespace components
