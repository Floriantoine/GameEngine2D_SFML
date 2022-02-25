#include "components/SpawnPosComponent.hpp"
#include "Game.hpp"

namespace components {
void SpawnPos::factory(id_t entityId, nlohmann::json config)
{
    sf::Vector2f initPos = {0, 0};
    sf::Vector2f rangeMin = {0, 0};
    sf::Vector2f rangeMax = {0, 0};

    if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr && config["init"].size() == 2) {
            initPos = sf::Vector2f(config["init"][0], config["init"][1]);
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
        initPos = sf::Vector2f(config[0], config[1]);
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::SpawnPos>(
            entityId, initPos, rangeMin, rangeMax);
}

SpawnPos::SpawnPos(nlohmann::json config)
{
    if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr && config["init"].size() == 2) {
            _initPos = sf::Vector2f(config["init"][0], config["init"][1]);
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
        _initPos = sf::Vector2f(config[0], config[1]);
    }
}

void SpawnPos::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("SpawnPosComponent")) {
    }
};
} // namespace components