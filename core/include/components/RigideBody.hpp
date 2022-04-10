#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class RigideBody : public fa::Component<RigideBody> {
  public:
    sf::Vector2f _cur_S;
    bool _haveGravity = true;
    bool _isKinematic = false;

  public:
    RigideBody(bool gravity, bool kinematic)
        : _haveGravity(gravity), _isKinematic(kinematic){};
    ~RigideBody() = default;
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};

} // namespace components