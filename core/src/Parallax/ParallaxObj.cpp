
#include "./ParallaxObj.hpp"
#include <SFML/System/Vector2.hpp>

namespace parallax {
sf::Vector2i winSizeG = {1920, 1080};

void ParallaxObj::update()
{
    if (!_inverted) {
        _pos.x -= 1 * _layerId;
        if (_pos.x < (int)(-(_layerSize.x))) {
            _pos.y = tools::generate_random_number(0, winSizeG.y / 2, -1);
            _pos.x =
                tools::generate_random_number(winSizeG.x, winSizeG.x * 2, -1);
        }
    } else {
        _pos.x += 1 * _layerId;
        if (_pos.x > (int)(winSizeG.x + _layerSize.x)) {
            _pos.y = tools::generate_random_number(0, winSizeG.y / 2, -1);
            _pos.x = tools::generate_random_number(-(winSizeG.x * 2), 0, 1);
        }
    }
    // float angle = 0;
    // if (_inverted)
    // angle = 180;
    // lib.displayImage(_spriteId, _pos, angle);

    _sprite.setPosition(sf::Vector2f(_pos.x, _pos.y));
}

ParallaxObj::ParallaxObj(
    std::string spritePath, int layerId, sf::RenderWindow *win, bool inverted)
    : AParallax(spritePath, layerId, win, inverted)
{
    _pos.y = tools::generate_random_number(0, winSizeG.y / 2, -1);
    if (!_inverted) {
        _pos.x = tools::generate_random_number(winSizeG.x, winSizeG.x * 2, -1);
    } else {
        _pos.x = tools::generate_random_number(-(winSizeG.x * 2), 0, 1);
    }
}

} // namespace parallax