#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class LifeTime : public fa::Component<LifeTime> {
  public:
    LifeTime() = default;
    ~LifeTime() = default;
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components