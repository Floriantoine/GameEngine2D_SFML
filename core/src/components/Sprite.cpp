#include "components/Sprite.hpp"
#include "Game.hpp"

namespace components {
void Sprite::factory(id_t entityId, nlohmann::json config)
{
    std::string textureName = "";

    if (config != nullptr) {
        if (config.type() == nlohmann::json::value_t::object &&
            config["textureName"] != nullptr) {
            textureName = config["textureName"];
        } else {
            textureName = config;
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Sprite>(entityId, textureName);
}
void Sprite::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("SpriteComponent")) {
        ImGui::Checkbox("isInit", &_isInit);
        ImGui::InputText(
            "textureName", (char *)_textureName.c_str(), _textureName.size());
    }
};
} // namespace components