
#include "./layerBackground.hpp"

namespace parallax {

LayerBackground::LayerBackground(
    std::string spritePath, int layerId, sf::RenderWindow *win, bool inverted)
    : AParallax(spritePath, layerId, win, inverted)
{
}

} // namespace parallax