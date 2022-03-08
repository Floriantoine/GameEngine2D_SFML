#pragma once

#include "component/ComponentManager.hpp"
#include "entity/Entity.hpp"
#include "observer/ObserverManager.hpp"
#include "system/SystemManager.hpp"

#include <memory>
#include <vector>

namespace factory {

class EntityFactory {
  private:
    ObserverManager &_observerManager;
    fa::ComponentManager &_componentManager;
    fa::SystemManager &_systemManager;

    std::unordered_map<id_t, fa::Entity *> _entityList;
    std::unordered_map<std::string, std::string> _entityRegister;

    void destroyEntity(fa::Entity *entity)
    {
        this->_componentManager.removeAllComponents(entity->getId());
        this->_entityList.erase(entity->getId());
    }

  public:
    EntityFactory(ObserverManager &observerManager,
        fa::ComponentManager &componentManager,
        fa::SystemManager &systemManager);
    ~EntityFactory();
    EntityFactory(const EntityFactory &) = delete;
    EntityFactory(EntityFactory &&) = delete;
    EntityFactory &operator=(const EntityFactory &) = delete;
    void init();
    void createEntity(std::string configPath);

    fa::Entity *saveEntity(fa::Entity *ptr)
    {
        this->_entityList.emplace(ptr->getId(), ptr);
        return this->_entityList[ptr->getId()];
    }
    fa::Entity *newEntity(std::string name)
    {
        // Add check if have entity with same id
        fa::Entity *ptr = new fa::Entity(name);
        return saveEntity(ptr);
    }
    fa::Entity *newEntity()
    {
        fa::Entity *ptr = new fa::Entity;
        return saveEntity(ptr);
    }

    fa::Entity *getEntity(id_t id)
    {
        const auto &it = this->_entityList.find(id);

        if (it != this->_entityList.end()) {
            return it->second;
        }
        std::cout << "No Entity for ID: " << id << std::endl;
        return nullptr;
    }

    void destroyEntity(id_t id)
    {
        fa::Entity *entity = this->getEntity(id);
        if (entity != nullptr) {
            this->destroyEntity(entity);
        }
    }
};

} // namespace factory