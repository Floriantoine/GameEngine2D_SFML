
#include "sprite/SpriteManager.hpp"
#include "Game.hpp"

namespace flowEngine {

void SpriteManager::createSprite(sf::Texture *texture)
{
    this->_sprites.push_back(Sprite(texture));
}

void SpriteManager::display()
{
    std::for_each(_sprites.begin(), _sprites.end(), [](Sprite sprite) {
        Game::Game::getInstance().getWindow()->draw(sprite.getSfSprite());
    });
}

SpriteManager::SpriteManager(/* args */)
{
}

SpriteManager::~SpriteManager()
{
}

} // namespace flowEngine
