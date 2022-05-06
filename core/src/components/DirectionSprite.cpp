
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

void DisplayImage(std::string textureName)
{
    sf::Sprite sprite;
    sf::Vector2f size = {50, 50};
    auto *textureInf =
        Game::Game::getInstance()._spiteSystem->getTexture(textureName);
    if (textureInf != nullptr) {
        sprite.setTexture(textureInf->_texture);
        sprite.setScale(size / (textureInf->_texture.getSize() /
                                   sf::Vector2f(textureInf->_step, 1)));
        sprite.setTextureRect(sf::IntRect(0, 0,
            textureInf->_texture.getSize().x / textureInf->_step,
            textureInf->_texture.getSize().y));
    }
    ImGui::Image(sprite);
}

void DirectionSprite::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("DirectionSpriteComponent##ImGuiModifierECS")) {
        if (ImGui::BeginChild("DirectionSpriteComponentChild##ImGuiModifier")) {
            sf::Sprite sprite;

            DisplayImage(this->_textureDirections["UP_LEFT"]);
            ImGui::SameLine();
            DisplayImage(this->_textureDirections["UP"]);
            ImGui::SameLine();
            DisplayImage(this->_textureDirections["UP_RIGHT"]);

            DisplayImage(this->_textureDirections["LEFT"]);
            ImGui::SameLine();
            DisplayImage(this->_textureDirections["STATIC"]);
            ImGui::SameLine();
            DisplayImage(this->_textureDirections["RIGHT"]);

            DisplayImage(this->_textureDirections["DOWN_LEFT"]);
            ImGui::SameLine();
            DisplayImage(this->_textureDirections["DOWN"]);
            ImGui::SameLine();
            DisplayImage(this->_textureDirections["DOWN_RIGHT"]);

            ImGui::EndChild();
        }
    }
};
} // namespace components