#pragma once

#include "behavior/Behavior.hpp"
#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class BehaviorComponent : public fa::Component<BehaviorComponent> {
  public:
    fa::behavior::Behavior _behavior;
    bool isInit = false;

    BehaviorComponent() = default;
    BehaviorComponent(fa::behavior::Behavior behavior) : _behavior(behavior)
    {
    }
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components