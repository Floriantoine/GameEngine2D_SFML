#include "imgui/ecs/EcsController.hpp"
#include "Game.hpp"

namespace imguiTools {

void EcsController::newEntity()
{
    fa::id_t currentId = _entityRef->getId();
    auto &compManager = Game::Game::getInstance().getComponentManager();

    auto compList = compManager.getEntityComponentList(currentId);
    for (auto &item: compList) {
        item->dislayImGuiPanel();
        // if (ImGui::Button("-##DeleteComponentImguiControl")) {
        // }
    }
}

void EcsController::popupAddComponent()
{
    if (ImGui::BeginPopup("addComponentPopup##EcsController")) {
        static int currentItem = 0;
        fa::id_t currentId = _entityRef->getId();
        auto &compManager = Game::Game::getInstance().getComponentManager();
        auto nameList =
            tools::vStringToChar(compManager.getRegisterComponentNameList());

        ImGui::ListBox("Components: ##EcsSelector", &currentItem, &nameList[0],
            nameList.size());
        if (ImGui::Button("+##addComponentToEntity")) {
            nlohmann::json _json;
            Game::Game::getInstance().getComponentManager().addComponent(
                nameList[currentItem], currentId, _json);
        }
        ImGui::EndPopup();
    }
}

void EcsController::popupRemoveComponent()
{
    if (ImGui::BeginPopup("removeComponentPopup##EcsController")) {
        ImGui::Text("Work in progress");
        ImGui::EndPopup();
    }
}

void EcsController::update(long elapsedtime)
{
    static int currentSelectorItem = -1;
    auto &entityF = Game::Game::getInstance().getEntityFactory();
    auto nameList = tools::vStringToChar(entityF.getEntitiesFullName());

    ImGui::Begin("EcsController");

    bool isOpen = 0;
    if (ImGui::BeginTabBar("globalTab##EcsController")) {
        if (ImGui::BeginTabItem("CreateEntity##EcsController")) {
            ImGui::Button("CreateEntity");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Editor##EcsController")) {
            if (ImGui::CollapsingHeader("Selector##EcsController")) {
                if (ImGui::ListBox("Entity##EcsSelector: ",
                        &currentSelectorItem, &nameList[0], nameList.size())) {
                    _entityRef = entityF.getEntity(
                        tools::stringToId(nameList[currentSelectorItem]));
                }
            }

            // ---------------Popup / Activator ------------------------------
            if (_entityRef != nullptr) {
                if (ImGui::Button("Add Component##EcsController")) {
                    ImGui::OpenPopup("addComponentPopup##EcsController");
                }
                ImGui::SameLine();
                if (ImGui::Button("Remove Component##EcsController")) {
                    ImGui::OpenPopup("removeComponentPopup##EcsController");
                }
                popupAddComponent();
                popupRemoveComponent();
            }
            // ----------------------------------------------------------------

            if (_entityRef != nullptr &&
                ImGui::CollapsingHeader("Entity Components##EcsController",
                    ImGuiTreeNodeFlags_Framed)) {
                ImGui::BeginChild("EntityComponentsChild##EcsController");
                newEntity();
                ImGui::EndChild();
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    // ImGui::TextInput();
    // ImGui::SameLine();

    ImGui::End();
}
} // namespace imguiTools