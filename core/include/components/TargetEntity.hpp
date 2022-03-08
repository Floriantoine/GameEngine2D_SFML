#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class TargetEntity : public fa::Component<TargetEntity> {
  public:
    id_t _target = 0;
    TargetEntity() = default;
    TargetEntity(id_t target) : _target(target){};
    ~TargetEntity() = default;
    void dislayImGuiPanel() override;
    static void factory(id_t entityId, nlohmann::json config);
};
} // namespace components