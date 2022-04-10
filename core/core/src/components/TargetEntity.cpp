#include "components/TargetEntity.hpp"
#include "Game.hpp"
#include "tools/tools.hpp"

namespace components {
void TargetEntity::factory(fa::id_t entityId, nlohmann::json config)
{
    fa::id_t targetId = -1;

    if (config != nullptr) {
        if (config.type() == nlohmann::json::value_t::number_unsigned) {
            targetId = config;
        }
        if (config.type() == nlohmann::json::value_t::string) {
            targetId = tools::stringToId(config);
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::TargetEntity>(entityId, targetId);
}
void TargetEntity::dislayImGuiPanel()
{
    auto &entityF = Game::Game::getInstance().getEntityFactory();
    auto nameList = tools::vStringToChar(entityF.getEntitiesFullName());

    if (ImGui::CollapsingHeader("TargetEntity##ImGuiModifier")) {
        if (ImGui::ListBox("TargetEntity##ImGuiModifier: ", &_imGuiCurrentItem,
                &nameList[0], nameList.size())) {
            fa::Entity *entity = entityF.getEntity(
                tools::stringToId(nameList[_imGuiCurrentItem]));
            if (entity != nullptr) {
                this->_target = entity->getId();
            }
        }
    }
};
} // namespace components