#include "components/Sprite.hpp"
#include "Game.hpp"

namespace components {
void Sprite::factory(id_t entityId, nlohmann::json config)
{
    std::string textureName;

    if (config["textureName"] != nullptr) {
        textureName = config["textureName"];
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Sprite>(entityId, textureName);
}
} // namespace components