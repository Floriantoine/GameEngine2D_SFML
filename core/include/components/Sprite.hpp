#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace components {

class Sprite : public rtype::Component<Sprite> {
  public:
    sf::Sprite _sprite;
    sf::Texture _texture;

  public:
    Sprite();
    ~Sprite() = default;
};
} // namespace components