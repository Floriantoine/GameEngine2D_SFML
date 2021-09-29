
#pragma once

#include "../tools/random.hpp"
#include "./AParallax.hpp"

namespace parallax {

class ParallaxLayer : public AParallax {
  public:
    void update() override;
    void display() override;
    ParallaxLayer(std::string spritePath, int layerId, sf::RenderWindow *win,
        bool inverted);
    ~ParallaxLayer() = default;
};

} // namespace parallax
