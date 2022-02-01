#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "Imgui.hpp"

namespace systems {

class FormSystem : public rtype::ASystem {
  private:
    int _data;

  public:
    FormSystem() : ASystem(){};
    ~FormSystem() = default;

    void update(long elapsedTime) override;
};
} // namespace systems