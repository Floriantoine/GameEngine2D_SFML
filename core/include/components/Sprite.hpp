#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace components {

class Sprite : public rtype::Component<Sprite> {
  public:
    sf::Sprite _sprite;
    std::string _textureName;
    int _isInit = false;

  public:
    Sprite(std::string textureName) : _textureName(textureName){};
    ~Sprite() = default;
};
} // namespace components