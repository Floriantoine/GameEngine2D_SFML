#include "system/EntitySpawner.hpp"
#include "Game.hpp"
#include "components/EntitySpawner.hpp"

namespace systems {
EntitySpawner::EntitySpawner(/* args */) : ASystem(){};

void EntitySpawner::update(long elapsedTime)
{
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        auto array = this->_componentManager
                         ->getComponentList<components::EntitySpawner>();

        for (auto &spawner: array) {
            components::EntitySpawner *spawnerComp =
                static_cast<components::EntitySpawner *>(spawner.second);
            if (spawnerComp->_spawnType ==
                components::EntitySpawner::SpawnType::NUMBER) {
                if (spawnerComp->_entityNumber > 0) {
                    Game::Game::getInstance().getEntityFactory().createEntity(
                        spawnerComp->_configPath);
                    spawnerComp->_entityNumber -= 1;
                }
            } else if (spawnerComp->_spawnType ==
                       components::EntitySpawner::SpawnType::TIME) {
                if (spawnerComp->_entityTime <=
                    spawnerComp->_clock.getElapsedTime().asMilliseconds()) {
                    sf::Int32 clockTime =
                        spawnerComp->_clock.getElapsedTime().asMilliseconds();
                    for (int i = 0; i < clockTime / spawnerComp->_entityTime;
                         i++) {
                        Game::Game::getInstance()
                            .getEntityFactory()
                            .createEntity(spawnerComp->_configPath);
                    }
                    spawnerComp->_clock.restart();
                }
            }
        }
        this->_elapsedTime = 0;
    }
}
} // namespace systems