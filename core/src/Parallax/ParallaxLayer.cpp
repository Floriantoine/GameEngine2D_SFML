#include "./ParallaxLayer.hpp"
#include <SFML/System/Vector2.hpp>

namespace parallax {

void ParallaxLayer::update()
{
    if (_layerId == 1)
        return;
    if (!_inverted)
        _pos.x -= 1 * _layerId;
    else
        _pos.x += 1 * _layerId;
    if (_pos.x < (int)(-_layerSize.x)) {
        _pos.x = 0;
    }
}

void ParallaxLayer::display()
{
    _sprite.setPosition(sf::Vector2f(_pos.x, _pos.y));
    _window->draw(_sprite);
    if (!_inverted) {
        _sprite.setPosition(sf::Vector2f(_pos.x + _layerSize.x, _pos.y));
        _window->draw(_sprite);
        _sprite.setPosition(
            sf::Vector2f(_pos.x + _layerSize.x + _layerSize.x, _pos.y));
        _window->draw(_sprite);
    } else {
        _sprite.setPosition(sf::Vector2f(_pos.x - _layerSize.x, _pos.y));
        _window->draw(_sprite);
        _sprite.setPosition(
            sf::Vector2f(_pos.x - _layerSize.x - _layerSize.x, _pos.y));
        _window->draw(_sprite);
    }
}

ParallaxLayer::ParallaxLayer(
    std::string spritePath, int layerId, sf::RenderWindow *win, bool inverted)
    : AParallax(spritePath, layerId, win, inverted)
{
    sf::Vector2i winSize = {1920, 1080};

    if (layerId != 1)
        _pos.y += tools::generate_random_number(0, winSize.y / 2, -1);
    _layerSize.x = winSize.x;
    _layerSize.y = winSize.y;
}

} // namespace parallax