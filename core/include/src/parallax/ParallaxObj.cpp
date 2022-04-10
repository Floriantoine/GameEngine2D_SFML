
#include "parallax/ParallaxObj.hpp"
#include "parallax/ParallaxSystem.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>

namespace parallax {
sf::Vector2i winSizeG = {1920, 1080};

void ParallaxObj::update(long elapsed)
{
    this->_totalLifeTime += elapsed;
    long step = this->_totalLifeTime / this->getParallaxManagerRef()->getRate();
    if (step)
        this->_totalLifeTime %= this->getParallaxManagerRef()->getRate();

    // _pos.y += tools::generate_random_number(0, 10, 0) - 5;

    if (!_inverted) {
        this->_pos.x -= step * this->_xStep;
        if (_pos.x < (int)(-(_layerSize.x))) {
            _pos.y = tools::generate_random_number(0, winSizeG.y / 2, -1);
            _pos.x =
                tools::generate_random_number(winSizeG.x, winSizeG.x * 2, -1);
            _initInY = _pos.y;
        }
    } else {
        this->_pos.x += step * this->_xStep;
        if (_pos.x > (int)(winSizeG.x + _layerSize.x)) {
            _pos.y = tools::generate_random_number(0, winSizeG.y / 2, -1);
            _pos.x = tools::generate_random_number(-(winSizeG.x * 2), 0, 1);
            _initInY = _pos.y;
        }
    }

    if (this->_amplitude != 0) {
        double sinValue = sin(this->_pos.x / this->_amplitude);
        this->_pos.y = this->_initInY + (this->_amplitude * sinValue);
    }
    _sprite.setPosition(sf::Vector2f(_pos.x, _pos.y));
}

ParallaxObj::ParallaxObj(ParallaxSystem *paraS, std::string spritePath,
    int layerId, sf::RenderWindow *win, nlohmann::json options)
    : AParallax(paraS, spritePath, layerId, win, options)
{
    _pos.y = tools::generate_random_number(0, winSizeG.y / 2, -1);
    _initInY = _pos.y;
    if (!_inverted) {
        _pos.x = tools::generate_random_number(winSizeG.x, winSizeG.x * 2, -1);
    } else {
        _pos.x = tools::generate_random_number(-(winSizeG.x * 2), 0, 1);
    }
}

} // namespace parallax