#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class TargetEntity : public rtype::Component<TargetEntity> {
  public:
    int _target = 0;
    TargetEntity() = default;
    TargetEntity(int target) : _target(target){};
    ~TargetEntity() = default;
    void dislayImGuiPanel() override;
    static void factory(id_t entityId, nlohmann::json config);
};
} // namespace components