#include "parallax/ParallaxLayer.hpp"
#include "parallax/ParallaxSystem.hpp"
#include <SFML/System/Vector2.hpp>

namespace parallax {

void ParallaxLayer::update(long elapsed)
{
    this->_totalLifeTime += elapsed;
    long step = _totalLifeTime / this->getParallaxManagerRef()->getRate();
    if (step)
        _totalLifeTime %= this->getParallaxManagerRef()->getRate();

    if (_layerId == 1)
        return;
    if (!_inverted)
        this->_pos.x -= step * this->_layerId;
    else
        this->_pos.x += step * this->_layerId;
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

ParallaxLayer::ParallaxLayer(ParallaxSystem *paraS, std::string spritePath,
    int layerId, sf::RenderWindow *win, nlohmann::json options)
    : AParallax(paraS, spritePath, layerId, win, options)
{
    sf::Vector2i winSize = {1920, 1080};

    if (layerId != 1)
        _pos.y += tools::generate_random_number(0, winSize.y / 2, -1);
    _layerSize.x = winSize.x;
    _layerSize.y = winSize.y;
}

} // namespace parallax