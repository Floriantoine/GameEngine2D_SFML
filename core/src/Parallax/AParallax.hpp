
#pragma once

#include "./IParallax.hpp"
#include <SFML/Graphics.hpp>

namespace parallax {

class AParallax : public IParallax {
  public:
    AParallax() = delete;
    AParallax(AParallax const &to_copy) noexcept;
    AParallax(AParallax &&to_move) = default;
    AParallax &operator=(AParallax const &to_copy);

    virtual ~AParallax() = default;

    void update() override;
    void display() override;

  protected:
    std::string _spritePath;
    int _layerId;
    bool _inverted;
    sf::Vector2i _pos;
    sf::Vector2u _layerSize;
    sf::RenderWindow *_window;
    sf::Texture _texture;
    sf::Sprite _sprite;

    AParallax(std::string spritePath, int layerId, sf::RenderWindow *win,
        bool inverted);
};

} // namespace parallax
