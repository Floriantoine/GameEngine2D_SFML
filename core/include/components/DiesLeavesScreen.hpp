#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class DiesLeavesScreen : public rtype::Component<DiesLeavesScreen> {
  public:
    DiesLeavesScreen() = default;
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components