#pragma once
#include "Imgui.hpp"
#include "entity/Entity.hpp"

namespace imguiTools {

class EcsController {
  private:
    static inline fa::Entity *_entityRef = nullptr;
    static inline bool _createEntity = false;
    static void newEntity();

  public:
    static void update(long elapsedtime);
    EcsController(/* args */) = default;
    ~EcsController() = default;
};

} // namespace imguiTools