#include "factory/EntityFactory.hpp"

namespace factory {

EntityFactory::EntityFactory(ObserverManager &observerManager,
    fa::ComponentManager &componentManager, fa::SystemManager &systemManager)
    : _observerManager(observerManager), _componentManager(componentManager),
      _systemManager(systemManager)
{
}

void EntityFactory::createEntity(std::string configPath)
{
    nlohmann::json _json = json::loadJson(configPath);

    if (_json == nlohmann::json::value_t::discarded || _json.is_discarded()) {
        std::cout << "Json Config Error: " << configPath << std::endl;
    } else {
        fa::Entity *entity = nullptr;
        if (_json["name"] != nullptr &&
            _json["name"].type() == nlohmann::json::value_t::string) {
            std::string name = _json["name"];
            entity = this->newEntity(name);
        } else {
            entity = this->newEntity();
        }
        if (entity != nullptr) {
            for (auto it = _json.begin(); it != _json.end(); ++it) {
                if (this->_componentManager.componentNameIsRegister(it.key())) {
                    this->_componentManager.addComponent(
                        it.key(), entity->getId(), it.value());
                } else {
                    std::cout << "Component: " << it.key() << " undefined"
                              << std::endl;
                }
            }
        }
    }
}

void EntityFactory::init()
{
    this->createEntity("../core/json/entity/Player.json");
    this->createEntity("../core/json/entity/Enemy.json");
    this->createEntity("../core/json/entity/Protector.json");
}

EntityFactory::~EntityFactory()
{
}

}; // namespace factory