#include "imgui/ecs/EcsController.hpp"
#include "Game.hpp"

namespace imguiTools {

EcsController::EcsController(/* args */)
{
}

EcsController::~EcsController()
{
}

void EcsController::newEntity()
{
}

void EcsController::update(long elapsedtime)
{
    ImGui::Begin("EcsController");

    if (ImGui::Button("CreateEntity")) {
        newEntity();
    }

    ImGui::End();
}
} // namespace imguiTools