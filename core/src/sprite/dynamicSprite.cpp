#include "dynamicSprite.hpp"
#include "Game.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
namespace flowEngine {

void dynamicSprite::setSprite(Sprite *sprite)
{
    _sprite = sprite;
    auto obs = new Observer{
        [&](MouseMove const &mouse) {
            if (!this->_attach && !this->_resize)
                _sprite->getSfSprite().setPosition(mouse.x, mouse.y);
            else if (this->_resize) {
                auto &tempoSprite = this->_sprite->getSfSprite();
                auto textureSize = tempoSprite.getTexture()->getSize();
                auto spritePos = tempoSprite.getPosition();

                _sprite->getSfSprite().setScale(
                    textureSize.x /
                        std::abs(
                            std::abs(spritePos.x - textureSize.x) - mouse.x),
                    textureSize.y /
                        std::abs(
                            std::abs(spritePos.y - textureSize.y) - mouse.y));
            }
        },
        [&](MouseClick const &mouse) {
            this->_attach = !this->_attach;
            if (this->_attach == false)
                _sprite->getSfSprite().setPosition(mouse.x, mouse.y);
        },
        [&](KeyPressed const &key) {
            if (key.key == sf::Keyboard::E) {
                auto &tempoSprite = this->_sprite->getSfSprite();
                tempoSprite.setRotation((tempoSprite.getRotation() + 2));
            } else if (key.key == sf::Keyboard::Q) {
                auto &tempoSprite = this->_sprite->getSfSprite();
                tempoSprite.setRotation((tempoSprite.getRotation() - 2));
            } else if (key.key == sf::Keyboard::O) {
                this->_resize = !this->_resize;
            }
        },
    };

    Game::Game::getInstance().getObserverManager().addObserver(obs);
};
} // namespace flowEngine