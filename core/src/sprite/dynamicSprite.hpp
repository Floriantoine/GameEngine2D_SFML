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
    Observer _observer;

  public:
    dynamicSprite() = default;
    ~dynamicSprite();
    void update();
    void setSprite(Sprite *sprite);
};

} // namespace flowEngine