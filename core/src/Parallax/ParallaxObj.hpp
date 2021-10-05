#pragma once

#include "./AParallax.hpp"
namespace parallax

{
class ParallaxObj : public AParallax {
  public:
    void update(long elapsed) override;
    ParallaxObj(ParallaxSystem *parallax, std::string spritePath, int layerId,
        sf::RenderWindow *win, nlohmann::json options);
    ~ParallaxObj() = default;
};

} // namespace parallax
