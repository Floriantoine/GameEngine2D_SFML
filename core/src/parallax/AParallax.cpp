#include "parallax/AParallax.hpp"
#include "parallax/ParallaxSystem.hpp"

namespace parallax {

AParallax::AParallax(AParallax const &to_copy) noexcept
    : _spritePath(to_copy._spritePath), _layerId(to_copy._layerId),
      _pos(to_copy._pos), _layerSize(to_copy._layerSize),
      _window(to_copy._window)
{
}

void AParallax::update(long elapsed)
{
}

void AParallax::display()
{
    _window->draw(_sprite);
}

AParallax::AParallax(ParallaxSystem *paraS, std::string spritePath, int layerId,
    sf::RenderWindow *win, nlohmann::json options)
    : _window(win), _spritePath(spritePath), _layerId(layerId), _pos({0, 0}),
      _layerSize({1920, 1080}), _inverted(false), _initInY(_pos.y),
      _parallaxManager(paraS)
{
    _texture.loadFromFile(_spritePath);
    _sprite.setTexture(_texture);

    if (options != nullptr) {
        if (options["inverted"] != nullptr && options["inverted"] == true)
            this->_inverted = true;
        if (options["xStep"] != nullptr)
            this->_xStep = options["xStep"];
        if (options["amplitude"] != nullptr)
            this->_amplitude = options["amplitude"];
    }
    if (_inverted == true)
        this->_sprite.scale(-1, 1);
}

} // namespace parallax