#pragma once

#include "../types.hpp"
#include "component/ComponentManager.hpp"

#include <iostream>

namespace rtype {

class ASystem {
    friend class SystemManager;

  public:
    enum system_group_e
    {
        UNKNOWN_SYSTEM_GROUP = -1,
        RENDER_SYSTEM_GROUP
    };

  private:
    system_group_e group_;

  protected:
    ComponentManager *componentManager_;

    ASystem(system_group_e group = UNKNOWN_SYSTEM_GROUP) : group_{group}
    {
    }
    ~ASystem() = default;

  public:
    virtual void update(long elapsedTime) = 0;

    system_group_e getGroup()
    {
        return this->group_;
    }
};

} // namespace rtype
