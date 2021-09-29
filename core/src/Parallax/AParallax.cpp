#include "./AParallax.hpp"

namespace parallax {

AParallax::AParallax(AParallax const &to_copy) noexcept
    : _spritePath(to_copy._spritePath), _layerId(to_copy._layerId),
      _pos(to_copy._pos), _layerSize(to_copy._layerSize),
      _window(to_copy._window)
{
}

void AParallax::update()
{
}

void AParallax::display()
{
    _window->draw(_sprite);
}

AParallax::AParallax(
    std::string spritePath, int layerId, sf::RenderWindow *win, bool inverted)
    : _window(win), _spritePath(spritePath), _layerId(layerId),
      _inverted(inverted), _pos({0, 0}), _layerSize({1920, 1080})
{
    _texture.loadFromFile(_spritePath);
    _sprite.setTexture(_texture);
    if (inverted == true)
        this->_sprite.scale(-1, 1);
}

} // namespace parallax