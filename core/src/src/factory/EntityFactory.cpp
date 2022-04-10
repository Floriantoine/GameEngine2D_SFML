#include "factory/EntityFactory.hpp"

namespace factory {

EntityFactory::EntityFactory(ObserverManager &observerManager,
    fa::ComponentManager &componentManager, fa::SystemManager &systemManager)
    : _observerManager(observerManager), _componentManager(componentManager),
      _systemManager(systemManager)
{
}

EntityFactory::~EntityFactory()
{
}

void EntityFactory::createEntityFromJson(nlohmann::json json)
{
    fa::Entity *entity = nullptr;
    if (json["name"] != nullptr &&
        json["name"].type() == nlohmann::json::value_t::string) {
        entity = this->newEntity(json["name"]);
    } else {
        entity = this->newEntity();
    }
    if (entity != nullptr) {
        fa::id_t id = entity->getId();
        for (auto it = json.begin(); it != json.end(); ++it) {
            if (this->_componentManager.componentNameIsRegister(it.key())) {
                this->_componentManager.addComponent(it.key(), id, it.value());
            } else {
                std::cout << "Component: " << it.key() << " is undefined on "
                          << entity->getName() << std::endl;
            }
        }
    }
}

void EntityFactory::createEntity(std::string configPath)
{
    nlohmann::json json = json::loadJson(configPath);

    if (json == nlohmann::json::value_t::discarded || json.is_discarded()) {
        std::cout << "Json Config Error: " << configPath << std::endl;
    } else {
        this->createEntityFromJson(json);
    }
}

void EntityFactory::init()
{
    this->createEntity("../core/json/entity/Player.json");
    this->createEntity("../core/json/entity/Enemy.json");
    this->createEntity("../core/json/entity/Protector.json");
    this->createEntity("../core/json/hud/Button.json");
    this->createEntity("../core/json/hud/platform.json");
}

std::vector<std::string> EntityFactory::getEntitiesName() const
{
    std::vector<std::string> names;
    for (auto entity: this->_entityList) {
        names.push_back(entity.second->getName());
    }
    return names;
}
std::vector<std::string> EntityFactory::getEntitiesFullName() const
{
    std::vector<std::string> names;
    for (auto entity: this->_entityList) {
        names.push_back(entity.second->getFullName());
    }
    return names;
}

fa::Entity *EntityFactory::saveEntity(fa::Entity *ptr)
{
    this->_entityList[ptr->getId()] = ptr;
    return this->_entityList[ptr->getId()];
}
fa::Entity *EntityFactory::newEntity(std::string name)
{
    // Add check if have entity with same id
    fa::Entity *ptr = new fa::Entity(name);
    return saveEntity(ptr);
}
fa::Entity *EntityFactory::newEntity()
{
    fa::Entity *ptr = new fa::Entity;
    return saveEntity(ptr);
}

fa::Entity *EntityFactory::getEntity(fa::id_t id)
{
    const auto &it = this->_entityList.find(id);

    if (it != this->_entityList.end()) {
        return it->second;
    }
    return nullptr;
}

void EntityFactory::destroyEntity(fa::id_t id)
{
    fa::Entity *entity = this->getEntity(id);
    if (entity != nullptr) {
        this->destroyEntity(entity);
    }
}

void EntityFactory::destroyEntity(fa::Entity *entity)
{
    this->_componentManager.removeAllComponents(entity->getId());
    this->_entityList.erase(entity->getId());
}

}; // namespace factory