
#pragma once

#include "../tools/random.hpp"
#include "./AParallax.hpp"

namespace parallax {

class ParallaxLayer : public AParallax {
  public:
    void update(long elapsed) override;
    void display() override;
    ParallaxLayer(ParallaxSystem *paraS, std::string spritePath, int layerId,
        sf::RenderWindow *win, nlohmann::json options);
    ~ParallaxLayer() = default;
};

} // namespace parallax
