
#pragma once

#include "../Imgui.hpp"
#include "./ComponentBase.hpp"

namespace fa {

template <typename T> class Component : public ComponentBase {
  public:
    static id_t getTypeId()
    {
        static id_t id = ComponentBase::getNextTypeId();
        return id;
    }
};

} // namespace fa
