#include "sprite/Sprite.hpp"
#include <iostream>

namespace flowEngine {

Sprite::Sprite(sf::Texture *texture) : _textureRef(texture)
{
    _sprite.setTexture(*_textureRef);
}

} // namespace flowEngine