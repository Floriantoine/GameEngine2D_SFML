#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class TargetEntity : public fa::Component<TargetEntity> {
  public:
    fa::id_t _target = 0;

    int _imGuiCurrentItem = 0;

    TargetEntity() = default;
    TargetEntity(fa::id_t target) : _target(target){};
    ~TargetEntity() = default;
    void dislayImGuiPanel() override;
    static void factory(fa::id_t entityId, nlohmann::json config);
};
} // namespace components