#include "sprite/Sprite.hpp"
#include <iostream>

namespace fa {

Sprite::Sprite(sf::Texture *texture) : _textureRef(texture)
{
    _sprite.setTexture(*_textureRef);
}

} // namespace fa