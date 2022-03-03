#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Vector2.hpp>

namespace components {

class ParentRef : public rtype::Component<ParentRef> {
  public:
    int _parentRef = -1;

  public:
    ParentRef() = default;
    ParentRef(nlohmann::json config);
    ParentRef(int parentRef) : _parentRef(parentRef)
    {
    }
    static void factory(id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components