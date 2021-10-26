#pragma once

#include "./Sprite.hpp"
#include "ObserverManager.hpp"
#include <SFML/System/Clock.hpp>

namespace flowEngine {

class dynamicSprite {
  protected:
    Sprite *_sprite;
    bool _attach = false;
    bool _resize = false;

  public:
    dynamicSprite() = default;
    ~dynamicSprite() = default;
    void update();
    void setSprite(Sprite *sprite);
};

} // namespace flowEngine