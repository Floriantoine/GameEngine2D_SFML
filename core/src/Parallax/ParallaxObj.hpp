#pragma once

#include "./AParallax.hpp"

namespace parallax

{

class ParallaxObj : public AParallax {
  public:
    void update() override;
    ParallaxObj(std::string spritePath, int layerId, sf::RenderWindow *win,
        bool inverted);
    ~ParallaxObj() = default;
};

} // namespace parallax
