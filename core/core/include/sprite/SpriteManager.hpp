#pragma once

#include "Sprite.hpp"

namespace fa {

class SpriteManager {
  private:
    std::vector<Sprite> _sprites;

  public:
    SpriteManager(/* args */);
    ~SpriteManager();
    void createSprite(sf::Texture *texture);
    std::vector<Sprite> &getSprites()
    {
        return _sprites;
    };
    void display();

    // void deleteSprite(int id);
    // Sprite const &getSpriteById(int id);
};

} // namespace fa
