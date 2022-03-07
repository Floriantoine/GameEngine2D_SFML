#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class SpawnMousePos : public fa::Component<SpawnMousePos> {
  public:
    SpawnMousePos() = default;
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components