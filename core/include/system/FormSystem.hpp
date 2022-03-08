#pragma once

#include "ASystem.hpp"

namespace systems {

class FormSystem : public fa::ASystem {
  private:
    int _data;

  public:
    FormSystem() : ASystem(){};
    ~FormSystem() = default;

    void update(long elapsedTime) override;
};
} // namespace systems