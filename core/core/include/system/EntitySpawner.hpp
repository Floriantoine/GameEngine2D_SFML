#pragma once
#include "ASystem.hpp"

namespace systems {

class EntitySpawner : public fa::ASystem {
  private:
    long _elapsedTime = 0;

  public:
    EntitySpawner(/* args */);
    ~EntitySpawner() = default;
    void update(long elapsedTime) override;
};
} // namespace systems
