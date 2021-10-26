#pragma once

#include <SFML/Graphics/Sprite.hpp>

namespace flowEngine {

class Sprite {
  private:
    sf::Sprite _sprite;
    sf::Texture *_textureRef;

  public:
    Sprite(sf::Texture *texture);
    ~Sprite() = default;

    sf::Sprite &getSfSprite()
    {
        return _sprite;
    };
};

} // namespace flowEngine