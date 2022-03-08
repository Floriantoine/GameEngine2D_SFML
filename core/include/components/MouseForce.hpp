#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class MouseForce : public fa::Component<MouseForce> {
  public:
    MouseForce() = default;
    ~MouseForce() = default;
    static void factory(fa::id_t entityId, nlohmann::json config);
};
} // namespace components