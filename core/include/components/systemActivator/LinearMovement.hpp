#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class LinearMovement : public fa::Component<LinearMovement> {
  public:
    std::string _direction;

  public:
    LinearMovement() = default;
    LinearMovement(std::string direction) : _direction(direction){};
    ~LinearMovement() = default;
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components