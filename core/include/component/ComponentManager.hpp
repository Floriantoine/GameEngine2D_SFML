
#pragma once

#include "../assert.hpp"
#include "../types.hpp"
#include "./ComponentBase.hpp"
#include "tools/Chrono.hpp"
#include "tools/jsonTools.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace fa {

class ComponentManager {
  private:
    typedef std::function<void(id_t entityId, const nlohmann::json &)>
        factory_function_t;
    std::unordered_map<id_t, std::unordered_map<id_t, ComponentBase *>>
        _componentLists;
    std::unordered_map<std::string, factory_function_t> _componentNamesList;

    bool isComponentTypeRegistered(id_t typeId) const;

    template <class T> bool isComponentTypeRegistered() const
    {
        return this->isComponentTypeRegistered(T::getTypeId());
    }

    std::unordered_map<id_t, ComponentBase *> &getComponentList(id_t typeId);

    bool hasComponent(id_t typeId, id_t entityId);

    ComponentBase *getComponent(id_t typeId, id_t entityId);

    void removeComponent(id_t typeId, id_t entityId);

  public:
    ComponentManager() = default;
    ComponentManager(const ComponentManager &) = delete;
    ComponentManager(ComponentManager &&) = delete;
    ~ComponentManager();

    ComponentManager &operator=(const ComponentManager &) = delete;

    void clear();

    int getComponentCount() const;
    std::vector<ComponentBase *> getEntityComponentList(id_t entity);

    template <class T>
    std::unordered_map<id_t, ComponentBase *> &getComponentList()
    {
        return this->getComponentList(T::getTypeId());
    }

    std::vector<std::string> getRegisterComponentNameList()
    {
        std::vector<std::string> nameList;
        for (auto &it: this->_componentNamesList) {
            nameList.push_back(it.first);
        }
        return nameList;
    }

    void registerComponentName(
        const std::string &name, factory_function_t factory)
    {
        auto it = this->_componentNamesList.find(name);
        if (it != this->_componentNamesList.end()) {
            std::cout << "component already register for: " << name
                      << std::endl;
            return;
        }
        this->_componentNamesList[name] = factory;
    }

    bool componentNameIsRegister(const std::string &name)
    {
        auto it = this->_componentNamesList.find(name);
        if (it != this->_componentNamesList.end()) {
            return true;
        }
        return false;
    }

    template <typename... Args>
    void addComponent(std::string name, id_t entityId, Args &&...args)
    {
        auto it = this->_componentNamesList.find(name);
        if (it == this->_componentNamesList.end()) {
            std::cout << "No Component register for: " << name << std::endl;
            return;
        }
        it->second(entityId, std::forward<Args>(args)...);
    }

    template <class T, typename... Args>
    void addComponent(id_t entityId, Args &&...args)
    {
        if (this->hasComponent<T>(entityId) != false) {
            std::cout << "Entity already has component" << std::endl;
            return;
            // throw std::overflow_error("Entity already has component");
        }
        T *component = new T(std::forward<Args>(args)...);
        this->getComponentList<T>()[entityId] =
            static_cast<ComponentBase *>(component);
    }

    template <class T, typename... Args>
    void addComponentRange(id_t startId, id_t endId, Args &&...args)
    {
        if (endId < startId)
            assert("Bad Range");
        for (fa::id_t index = startId; index < endId; index++) {
            addComponent<T>(index, std::forward<Args>(args)...);
        }
    }

    template <class T> bool hasComponent(id_t entityId)
    {
        return this->hasComponent(T::getTypeId(), entityId);
    }

    template <class T> T *getComponent(id_t entityId)
    {
        STATIC_ASSERT_IS_COMPONENT(T);
        return static_cast<T *>(this->getComponent(T::getTypeId(), entityId));
    }

    template <class T> void removeComponentRange(id_t startId, id_t endId)
    {
        if (endId < startId)
            assert("Bad Range");
        for (fa::id_t index = startId; index < endId; index++) {
            this->removeComponent(T::getTypeId(), index);
        }
    }

    template <class T> void removeComponent(id_t entityId)
    {
        if (this->hasComponent<T>(entityId) == false)
            throw std::overflow_error("Entity does not have component");
        this->removeComponent(T::getTypeId(), entityId);
    }

    void removeAllComponents(id_t entityId);
    void removeAllComponentsRange(id_t entityIdMin, id_t entityIdMax);

    template <class T> void apply(std::function<void(T *)> function)
    {
        const auto &list = this->getComponentList<T>();
        for (auto it = list.begin(), next = it; it != list.end(); it = next) {
            next++;
            function(static_cast<T *>(it->second));
        }
    }

    template <class T>
    void apply(std::function<void(
            T *, id_t, const std::unordered_map<id_t, ComponentBase *> &)>
            function)
    {
        if (this->isComponentTypeRegistered<T>()) {
            const auto &list = this->getComponentList<T>();
            for (auto it = list.begin(), next = it; it != list.end();
                 it = next) {
                next++;
                function(static_cast<T *>(it->second), it->first, list);
            }
        }
    }

    template <class T>
    void apply(id_t entityId, std::function<void(T *)> function)
    {
        function(static_cast<T *>(this->getComponent<T>(entityId)));
    }
};
} // namespace fa