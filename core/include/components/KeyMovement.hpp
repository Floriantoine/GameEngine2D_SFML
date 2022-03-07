#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class KeyMovement : public fa::Component<KeyMovement> {
  public:
    KeyMovement() = default;
    ~KeyMovement() = default;
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components