
#pragma once

#include "./AParallax.hpp"
#include <SFML/Window.hpp>

namespace parallax {

class LayerBackground : public AParallax {
  public:
    LayerBackground(std::string spritePath, int layerId, sf::RenderWindow *win,
        bool inverted);
    ~LayerBackground() = default;
};

} // namespace parallax
