#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class MouseForce : public rtype::Component<MouseForce> {
  public:
    MouseForce() = default;
    ~MouseForce() = default;
    static void factory(id_t entityId, nlohmann::json config);
};
} // namespace components