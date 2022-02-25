#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class SolidBlock : public rtype::Component<SolidBlock> {
  public:
    bool _haveCollision = false;
    int _targetId;

    SolidBlock() = default;
    ~SolidBlock() = default;
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components