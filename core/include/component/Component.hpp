
#pragma once

#include "./ComponentBase.hpp"

namespace rtype {

template <typename T> class Component : public ComponentBase {
  public:
    static id_t getTypeId()
    {
        static id_t id = ComponentBase::getNextTypeId();
        return id;
    }
};

} // namespace rtype
