#pragma once

#include "component/Component.hpp"

namespace components {

class MasseComponent : public rtype::Component<MasseComponent> {
  public:
    int masse{1};
    int _initMasse{1};

  public:
    MasseComponent() = default;
    MasseComponent(int masse) : masse{masse}, _initMasse{masse}
    {
    }
};
} // namespace components