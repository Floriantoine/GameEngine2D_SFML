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

    std::unordered_map<fa::id_t, fa::Entity *> _entityList;
    std::unordered_map<std::string, std::string> _entityRegister;

    void destroyEntity(fa::Entity *entity);

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
    std::vector<std::string> getEntitiesName() const;
    std::vector<std::string> getEntitiesFullName() const;

    fa::Entity *saveEntity(fa::Entity *ptr);
    fa::Entity *newEntity(std::string name);
    fa::Entity *newEntity();
    fa::Entity *getEntity(fa::id_t id);
    void destroyEntity(fa::id_t id);
};

} // namespace factory