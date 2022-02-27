
#include "components/systemActivator/PresseSpaceMakeEntity.hpp"
#include "Game.hpp"

namespace components {
void PresseSpaceMakeEntity::factory(id_t entityId, nlohmann::json config)
{
    std::string path = "";
    if (config.type() == nlohmann::json::value_t::string) {
        path = config;
    }

    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::PresseSpaceMakeEntity>(entityId, path);
}
PresseSpaceMakeEntity::PresseSpaceMakeEntity(std::string path)
    : _configPath(path)
{
}

void PresseSpaceMakeEntity::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader(
            "PresseSpaceMakeEntityComponent##ImGuiModifier")) {
    }
};
} // namespace components