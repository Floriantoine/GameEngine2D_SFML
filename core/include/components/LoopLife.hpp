#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class LoopLife : public rtype::Component<LoopLife> {
  public:
    static void factory(id_t entityId, nlohmann::json config);
    LoopLife() = default;
    ~LoopLife() = default;
};
} // namespace components