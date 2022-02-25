#pragma once
#include "Imgui.hpp"

namespace imguiTools {

class EcsController {
  private:
    static inline bool _createEntity = false;
    static void newEntity();

  public:
    static void update(long elapsedtime);
    EcsController(/* args */) = default;
    ~EcsController() = default;
};

} // namespace imguiTools