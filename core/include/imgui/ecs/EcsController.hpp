#pragma once
#include "Imgui.hpp"

namespace imguiTools {

class EcsController {
  private:
  public:
    EcsController(/* args */);
    ~EcsController();
    void update(long elapsedtime);
    void newEntity();
};

} // namespace imguiTools