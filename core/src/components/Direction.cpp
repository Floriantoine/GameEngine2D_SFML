
#include "components/Direction.hpp"
#include "Game.hpp"

namespace components {
void Direction::factory(fa::id_t entityId, nlohmann::json config)
{
    sf::Vector2i direction(0, 0);
    bool continuous = false;

    if (config != nullptr) {
        if (config.type() == nlohmann::json::value_t::string) {
            if (config == "UP")
                direction = directions::UP;
            else if (config == "UP_LEFT")
                direction = directions::UP_LEFT;
            else if (config == "UP_RIGHT")
                direction = directions::UP_RIGHT;
            else if (config == "LEFT")
                direction = directions::LEFT;
            else if (config == "STATIC")
                direction = directions::STATIC;
            else if (config == "RIGHT")
                direction = directions::RIGHT;
            else if (config == "DOWN_LEFT")
                direction = directions::DOWN_LEFT;
            else if (config == "DOWN")
                direction = directions::DOWN;
            else if (config == "DOWN_RIGHT")
                direction = directions::DOWN_RIGHT;
        } else if (config.type() == nlohmann::json::value_t::array) {
            if (config.size() == 2) {
                direction = sf::Vector2i(config[0], config[1]);
            }
        } else if (config.type() == nlohmann::json::value_t::object) {
            if (config["direction"] != nullptr) {
                if (config["direction"].type() ==
                    nlohmann::json::value_t::string) {
                    if (config["direction"] == "UP")
                        direction = directions::UP;
                    else if (config["direction"] == "UP_LEFT")
                        direction = directions::UP_LEFT;
                    else if (config["direction"] == "UP_RIGHT")
                        direction = directions::UP_RIGHT;
                    else if (config["direction"] == "LEFT")
                        direction = directions::LEFT;
                    else if (config["direction"] == "STATIC")
                        direction = directions::STATIC;
                    else if (config["direction"] == "RIGHT")
                        direction = directions::RIGHT;
                    else if (config["direction"] == "DOWN_LEFT")
                        direction = directions::DOWN_LEFT;
                    else if (config["direction"] == "DOWN")
                        direction = directions::DOWN;
                    else if (config["direction"] == "DOWN_RIGHT")
                        direction = directions::DOWN_RIGHT;
                } else if (config["direction"].type() ==
                           nlohmann::json::value_t::array) {
                    if (config["direction"].size() == 2) {
                        direction = sf::Vector2i(
                            config["direction"][0], config["direction"][1]);
                    }
                }
            }
            if (config["continuous"] != nullptr &&
                config["continuous"].type() ==
                    nlohmann::json::value_t::boolean) {
                continuous = config["continuous"];
            }
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Direction>(entityId, direction, continuous);
}
void Direction::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("directionComponent##ImGuiModifierECS")) {
        ImGui::Checkbox("IsContinuous##ImGuiModifierECS", &_continuous);
    }
};
} // namespace components