
#include "components/PosComponent.hpp"
#include "Game.hpp"

namespace components {
void PosComponent::factory(id_t entityId, nlohmann::json config)
{
    sf::Vector2f pos = {0, 0};
    if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr && config["init"].size() == 2) {
            pos = sf::Vector2f(config["init"][0], config["init"][1]);
        }
    } else if (config.type() == nlohmann::json::value_t::array &&
               config[0] != nullptr && config[1] != nullptr) {
        pos = sf::Vector2f(config[0], config[1]);
    }

    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::PosComponent>(entityId, pos);
}
PosComponent::PosComponent(nlohmann::json config)
{
    if (config.type() == nlohmann::json::value_t::object) {
        if (config["init"] != nullptr && config["init"].size() == 2) {
            this->_pos = sf::Vector2f(config["init"][0], config["init"][1]);
        }
    } else if (config.type() == nlohmann::json::value_t::array &&
               config[0] != nullptr && config[1] != nullptr) {
        _pos = sf::Vector2f(config[0], config[1]);
    }
}
void PosComponent::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("PosComponentComponent")) {
    }
};
} // namespace components