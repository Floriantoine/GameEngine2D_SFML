
#include "components/hud/Text.hpp"
#include "Game.hpp"

namespace components {
void Text::factory(fa::id_t entityId, nlohmann::json config)
{
    std::string string = "";
    std::string fontPath = "../core/resources/font/defaultFont.ttf";

    if (config != nullptr) {
        if (config.type() == nlohmann::json::value_t::string) {
            string = config;
        } else if (config.type() == nlohmann::json::value_t::object) {
            if (config["string"] != nullptr &&
                config["string"].type() == nlohmann::json::value_t::string) {
                string = config["string"];
            }
            if (config["fontPath"] != nullptr &&
                config["fontPath"].type() == nlohmann::json::value_t::string) {
                fontPath = config["fontPath"];
            }
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Text>(entityId, string, fontPath);
}
void Text::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("TextComponent##ImGuiModifier")) {
    }
};
} // namespace components