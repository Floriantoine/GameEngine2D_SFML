#include "components/ForceComponent.hpp"
#include "Game.hpp"

namespace components {
void ForceComponent::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("ForceComponent")) {
        ImGui::InputFloat2("CurrentForce", &_initForce.x);
        ImGui::SliderFloat2("ForceRangeMin", &_rangeMin.x, 0, 100);
        ImGui::SliderFloat2("ForceRangeMax", &_rangeMax.x, 0, 100);
    }
};
void ForceComponent::factory(id_t entityId, nlohmann::json config)
{
    sf::Vector2f initForce = {0, 0};
    sf::Vector2f rangeMin = {0, 0};
    sf::Vector2f rangeMax = {0, 0};

    if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr && config["init"].size() == 2) {
            initForce = sf::Vector2f(config["init"][0], config["init"][1]);
        }
        if (config["rangeMin"] != nullptr && config["rangeMin"].size() == 2) {
            rangeMin =
                sf::Vector2f(config["rangeMin"][0], config["rangeMin"][1]);
        }
        if (config["rangeMax"] != nullptr && config["rangeMax"].size() == 2) {
            rangeMax =
                sf::Vector2f(config["rangeMax"][0], config["rangeMax"][1]);
        }
    } else if (config.type() == nlohmann::json::value_t::array &&
               config[0] != nullptr && config[1] != nullptr) {
        initForce = sf::Vector2f(config[0], config[1]);
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::ForceComponent>(
            entityId, initForce, rangeMin, rangeMax);
}

ForceComponent::ForceComponent(nlohmann::json config)
{
    if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr && config["init"].size() == 2) {
            _initForce = sf::Vector2f(config["init"][0], config["init"][1]);
            force = _initForce;
        }
        if (config["rangeMin"] != nullptr && config["rangeMin"].size() == 2) {
            _rangeMin =
                sf::Vector2f(config["rangeMin"][0], config["rangeMin"][1]);
        }
        if (config["rangeMax"] != nullptr && config["rangeMax"].size() == 2) {
            _rangeMax =
                sf::Vector2f(config["rangeMax"][0], config["rangeMax"][1]);
        }
    } else if (config.type() == nlohmann::json::value_t::array &&
               config[0] != nullptr && config[1] != nullptr) {
        _initForce = sf::Vector2f(config[0], config[1]);
        force = _initForce;
    }
}

ForceComponent::ForceComponent(
    sf::Vector2f initForce, sf::Vector2f rangeMin, sf::Vector2f rangeMax)
    : _initForce(initForce), _rangeMin(rangeMin), _rangeMax(rangeMax)
{
}
} // namespace components
