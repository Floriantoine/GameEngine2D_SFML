
#pragma once

#include "../tools/random.hpp"
#include <SFML/System/Vector2.hpp>

namespace parallax {

class IParallax {
  public:
    enum class ParallaxType : int
    {
        BACKGROUND = 0,
        LAYER,
        OBJ,
    };

    virtual ~IParallax() = default;
    IParallax(IParallax const &to_copy) = default;
    IParallax(IParallax &&to_move) = default;
    IParallax &operator=(IParallax const &to_copy) = default;

    virtual void update() = 0;
    virtual void display() = 0;

  protected:
    IParallax() = default;
};

} // namespace parallax