#include "components/EntitySpawner.hpp"
#include "Game.hpp"

namespace components {

void EntitySpawner::factory(fa::id_t entityId, nlohmann::json config)
{
    SpawnType spawnType = SpawnType::NUMBER;
    int entityNumber = 1;
    int entityTime = 1000;
    std::string configPath = "";

    if (config != nullptr && config.type() == nlohmann::json::value_t::object) {
        if (config["type"] != nullptr &&
            config["type"].type() == nlohmann::json::value_t::string) {
            if (config["type"] == "TIME") {
                spawnType = SpawnType::TIME;
            }
            if (config["type"] == "NUMBER") {
                spawnType = SpawnType::NUMBER;
            }
            if (config["type"] == "RANDOM") {
                spawnType = SpawnType::RANDOM;
            }
        }
        if (config["config"] != nullptr &&
            config["config"].type() == nlohmann::json::value_t::string) {
            configPath = config["config"];
        }
        std::cout << "coucou: " << (int)config["elapses"].type() << std::endl;
        if (config["elapses"] != nullptr &&
            config["elapses"].type() ==
                nlohmann::json::value_t::number_unsigned) {
            entityTime = config["elapses"];
        }
        if (config["iteration"] != nullptr &&
            config["iteration"].type() ==
                nlohmann::json::value_t::number_unsigned) {
            entityNumber = config["iteration"];
        }
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::EntitySpawner>(
            entityId, spawnType, entityNumber, entityTime, configPath);
}

void EntitySpawner::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader("EntitySpawner##ImGuiModifier")) {
        int currentItem = (int)_spawnType;
        std::vector<std::string> list = {"NUMBER", "TIME", "RANDOM"};
        auto charList = tools::vStringToChar(list);
        if (ImGui::BeginChild("EntitySpawnerChild##ImGuiModifier")) {
            ImGui::InputInt("NumberOfEntity##EntitySpawnerChildImGuiModifier",
                &this->_entityNumber);
            ImGui::InputInt("TimeBetweenSpawn##EntitySpawnerChildImGuiModifier",
                &this->_entityTime);
            ImGui::ListBox("SpawnerType##EntitySpawnerChildImGuiModifier",
                &currentItem, &charList[0], charList.size());
            if (currentItem != (int)_spawnType) {
                _spawnType = (SpawnType)currentItem;
            }
            // ImGui::InputText(
            // "EntityConfigPath##EntitySpawnerChildImGuiModifier",
            // _configPath.c_str(), _configPath.size());
            ImGui::EndChild();
        }
    }
}

} // namespace components