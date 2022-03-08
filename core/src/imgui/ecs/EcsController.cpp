#include "imgui/ecs/EcsController.hpp"
#include "Game.hpp"

namespace imguiTools {

void EcsController::newEntity()
{
    static int currentItem = 0;
    fa::id_t currentId = _entityRef->getId();
    auto &compManager = Game::Game::getInstance().getComponentManager();

    auto nameList =
        tools::vStringToChar(compManager.getRegisterComponentNameList());

    // ImGui::InputInt("Current EntityId: ", &currentId);
    ImGui::InputInt("Current Item: ##EcsSelector", &currentItem);
    ImGui::ListBox("Components: ##EcsSelector", &currentItem, &nameList[0],
        nameList.size());
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
    static int currentSelectorItem = -1;
    auto &entityF = Game::Game::getInstance().getEntityFactory();
    auto nameList = tools::vStringToChar(entityF.getEntitiesFullName());

    ImGui::Begin("EcsController");
    // ImGui::TextInput();
    // ImGui::SameLine();
    ImGui::Button("CreateEntity");

    if (ImGui::ListBox("Entity##EcsSelector: ", &currentSelectorItem,
            &nameList[0], nameList.size())) {
        _entityRef =
            entityF.getEntity(tools::stringToId(nameList[currentSelectorItem]));
    }

    if (_entityRef != nullptr) {
        newEntity();
    }

    ImGui::End();
}
} // namespace imguiTools