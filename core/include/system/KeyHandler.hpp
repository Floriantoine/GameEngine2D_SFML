#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "observer/Observer.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace systems {

class KeyHandler : public fa::ASystem {
  public:
    KeyHandler();
    ~KeyHandler() = default;

    void update(long elapsedTime) override;

  private:
    long _elapsedTime = 0;
    Subject _subject;
    std::vector<int> _keysPressed;
    Observer _observer;
};
} // namespace systems
