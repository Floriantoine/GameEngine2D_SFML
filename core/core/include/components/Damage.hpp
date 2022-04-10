#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"

namespace components {

class Damage : public fa::Component<Damage> {
  public:
    int _damage = 0;
    Damage() = default;
    Damage(int damage) : _damage(damage)
    {
    }
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components