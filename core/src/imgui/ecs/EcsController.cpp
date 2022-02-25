#include "imgui/ecs/EcsController.hpp"
#include "Game.hpp"

namespace imguiTools {

void EcsController::newEntity()
{
    static int currentItem = 0;
    static int currentId = 0;
    auto &compManager = Game::Game::getInstance().getComponentManager();

    auto nameList = compManager.getRegisterComponentNameList();
    std::vector<char *> array;
    array.reserve(nameList.size());

    for (auto &item: nameList) {
        array.push_back(const_cast<char *>(item.c_str()));
    }

    ImGui::InputInt("Current EntityId: ", &currentId);
    ImGui::InputInt("Current Item: ", &currentItem);
    ImGui::ListBox("Components: ", &currentItem, &array[0], array.size());
    if (ImGui::Button("+##addComponentToEntity")) {
        nlohmann::json _json;
        Game::Game::getInstance().getComponentManager().addComponent(
            nameList[currentItem], currentId, _json);
    }

    auto compList = compManager.getEntityComponentList(currentId);
    for (auto &item: compList) {
        item->dislayImGuiPanel();
        // if (ImGui::Button("-##DeleteComponentImguiControl")) {
        // }
    }
}

void EcsController::update(long elapsedtime)
{
    ImGui::Begin("EcsController");

    if (!_createEntity) {
        if (ImGui::Button("CreateEntity"))
            _createEntity = true;
    } else {
        newEntity();
    }

    ImGui::End();
}
} // namespace imguiTools