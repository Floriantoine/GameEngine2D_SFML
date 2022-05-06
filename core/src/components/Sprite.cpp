#include "components/Sprite.hpp"
#include "Game.hpp"

namespace components {
void Sprite::factory(fa::id_t entityId, nlohmann::json config)
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
    if (ImGui::CollapsingHeader("SpriteComponent##ImGuiPanel")) {
        auto *systemRef = Game::Game::getInstance()._spiteSystem.get();
        if (systemRef != nullptr) {
            std::vector<std::string> stringNames = systemRef->getTexturesName();
            auto charNames = tools::vStringToChar(stringNames);
            auto iter =
                std::find(stringNames.begin(), stringNames.end(), _textureName);
            int current = 0;
            if (iter != stringNames.end()) {
                current = iter - stringNames.begin();
            }
            if (ImGui::ListBox("textureName##ImGuiPanelListBox", &current,
                    &charNames[0], stringNames.size())) {
                _isInit = false;
                _textureName = stringNames[current];
            }
        }
        ImGui::InputInt(
            "updateTime##ImGuiECSModifierspriteComp", &_elapseUpdate);

        if (this->_isInit) {
            ImGui::Image(_sprite);
        }
    }
};
} // namespace components