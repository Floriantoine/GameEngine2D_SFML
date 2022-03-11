#pragma once

#include "ASystem.hpp"
#include "observer/Observer.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace systems {

class KeyMovement : public fa::ASystem {
  public:
    KeyMovement();
    ~KeyMovement() = default;

    void update(long elapsedTime) override;

  private:
    Observer _observers;
    long _elapsedTime = 0;
    sf::Vector2i _direction{0, 0};
};
} // namespace systems
