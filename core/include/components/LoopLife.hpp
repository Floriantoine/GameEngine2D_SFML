#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class LoopLife : public fa::Component<LoopLife> {
  public:
    static void factory(fa::id_t entityId, nlohmann::json config);
    LoopLife() = default;
    ~LoopLife() = default;
    void dislayImGuiPanel() override;
};
} // namespace components