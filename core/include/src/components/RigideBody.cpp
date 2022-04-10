
#include "Game.hpp"
#include "components/RigideBody.hpp"

namespace components {
void RigideBody::factory(fa::id_t entityId, nlohmann::json config)
{
    bool gravity = true;
    bool isKinematic = false;

    if (config.type() == nlohmann::json::value_t::object) {
        if (config["gravity"] != nullptr &&
            config["gravity"].type() == nlohmann::json::value_t::boolean) {
            gravity = config["gravity"];
        }
        if (config["isKinematic"] != nullptr &&
            config["isKinematic"].type() == nlohmann::json::value_t::boolean) {
            isKinematic = config["isKinematic"];
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::RigideBody>(entityId, gravity, isKinematic);
}
void RigideBody::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("RigideBody##ImGuiModifier")) {
        ImGui::Checkbox("gravity##RigideBodyImGuiModifier", &_haveGravity);
        ImGui::Checkbox("isKinematic##RigideBodyImGuiModifier", &_isKinematic);
    }
};
} // namespace components