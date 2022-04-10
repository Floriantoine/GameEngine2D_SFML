
#include "components/DirectionSprite.hpp"
#include "Game.hpp"

namespace components {
void DirectionSprite::factory(fa::id_t entityId, nlohmann::json config)
{
    std::unordered_map<std::string, std::string> directionsTexture;
    std::vector<std::string> DirectionsString = {"UP_LEFT", "UP", "UP_RIGHT",
        "LEFT", "STATIC", "RIGHT", "DOWN_LEFT", "DOWN", "DOWN_RIGHT"};

    if (config != nullptr) {
        if (config.type() == nlohmann::json::value_t::object) {
            for (auto &stringDirection: DirectionsString) {
                if (config[stringDirection] != nullptr &&
                    config[stringDirection].type() ==
                        nlohmann::json::value_t::string) {
                    directionsTexture[stringDirection] =
                        config[stringDirection];
                }
            }
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::DirectionSprite>(entityId, directionsTexture);
}
void DirectionSprite::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("DirectionSpriteComponent##ImGuiModifierECS")) {
        if (ImGui::BeginChild("DirectionSpriteComponentChild##ImGuiModifier")) {
            ImGui::EndChild();
        }
    }
};
} // namespace components