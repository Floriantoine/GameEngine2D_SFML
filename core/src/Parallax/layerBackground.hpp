
#pragma once

#include "./AParallax.hpp"
#include <SFML/Window.hpp>

namespace parallax {

class LayerBackground : public AParallax {
  public:
    LayerBackground(ParallaxSystem *paraS, std::string spritePath, int layerId,
        sf::RenderWindow *win, nlohmann::json options);
    ~LayerBackground() = default;
};

} // namespace parallax
