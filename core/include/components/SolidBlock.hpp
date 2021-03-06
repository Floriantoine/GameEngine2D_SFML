#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class SolidBlock : public fa::Component<SolidBlock> {
  public:
    bool _haveCollision = false;
    std::vector<fa::id_t> _targetsId;

    SolidBlock() = default;
    ~SolidBlock() = default;
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components