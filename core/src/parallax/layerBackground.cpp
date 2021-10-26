
#include "./layerBackground.hpp"

namespace parallax {

LayerBackground::LayerBackground(ParallaxSystem *paraS, std::string spritePath,
    int layerId, sf::RenderWindow *win, nlohmann::json options)
    : AParallax(paraS, spritePath, layerId, win, options)
{
}

} // namespace parallax