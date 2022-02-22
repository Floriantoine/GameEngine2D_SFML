#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

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
    static void factory(id_t entityId, nlohmann::json config);
};
} // namespace components