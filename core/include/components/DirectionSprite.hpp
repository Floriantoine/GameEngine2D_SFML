#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class DirectionSprite : public fa::Component<DirectionSprite> {
  public:
    DirectionSprite();
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components