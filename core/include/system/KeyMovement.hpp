#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "observer/Observer.hpp"
#include "observer/ObserverManager.hpp"
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
    std::string _direction = "";
};
} // namespace systems
