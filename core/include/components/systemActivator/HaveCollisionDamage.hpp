#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class HaveCollisionDamage : public fa::Component<HaveCollisionDamage> {
  public:
    HaveCollisionDamage() = default;
    ~HaveCollisionDamage() = default;
    void dislayImGuiPanel() override;
    static void factory(id_t entityId, nlohmann::json config);
};
} // namespace components