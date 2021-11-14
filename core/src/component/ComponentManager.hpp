/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Component manager class
*/

#pragma once

#include "../assert.hpp"
#include "../types.hpp"
#include "./ComponentBase.hpp"

#include <cassert>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace rtype {

class ComponentManager {
  private:
    std::unordered_map<id_t, std::unordered_map<id_t, ComponentBase *>>
        componentLists_;

    bool isComponentTypeRegistered(id_t typeId) const
    {
        return (
            this->componentLists_.find(typeId) != this->componentLists_.end());
    }

    template <class T> bool isComponentTypeRegistered() const
    {
        return this->isComponentTypeRegistered(T::getTypeId());
    }

    std::unordered_map<id_t, ComponentBase *> &getComponentList(id_t typeId)
    {
        auto it = this->componentLists_.find(typeId);
        if (it == this->componentLists_.end()) {
            assert("Component type not registered");
            this->componentLists_.emplace(typeId, 512);
            it = this->componentLists_.find(typeId);
        }
        return it->second;
    }

    template <class T>
    std::unordered_map<id_t, ComponentBase *> &getComponentList()
    {
        return this->getComponentList(T::getTypeId());
    }

    bool hasComponent(id_t typeId, id_t entityId)
    {
        if (this->isComponentTypeRegistered(typeId) == false)
            return false;
        const auto &list = this->getComponentList(typeId);
        return (list.find(entityId) != list.end());
    }

    ComponentBase *getComponent(id_t typeId, id_t entityId)
    {
        if (this->isComponentTypeRegistered(typeId) == false)
            return nullptr;
        const auto &list = this->getComponentList(typeId);
        const auto &it = list.find(entityId);
        if (it == list.end())
            return nullptr;
        return it->second;
    }

    void removeComponent(id_t typeId, id_t entityId)
    {
        this->getComponentList(typeId).erase(entityId);
    }

  public:
    ComponentManager() = default;
    ComponentManager(const ComponentManager &) = delete;
    ComponentManager(ComponentManager &&) = delete;
    ~ComponentManager() = default;

    ComponentManager &operator=(const ComponentManager &) = delete;

    void clear()
    {
        this->componentLists_.clear();
    }
    template <class T, typename... Args>
    void addComponent(id_t entityId, Args &&...args)
    {
        assert(this->hasComponent<T>(entityId) == false &&
               "Entity already has component");
        T *component = new T(std::forward<Args>(args)...);
        this->getComponentList<T>()[entityId] =
            static_cast<ComponentBase *>(component);
    }

    template <class T, typename... Args>
    void addComponentRange(id_t startId, id_t endId, Args &&...args)
    {
        if (endId < startId)
            assert("Bad Range");
        for (startId; startId < endId; startId++) {
            assert(this->hasComponent<T>(startId) == false &&
                   "Entity already has component");
            T *component = new T(std::forward<Args>(args)...);
            this->getComponentList<T>()[startId] =
                static_cast<ComponentBase *>(component);
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

    template <class T> void removeComponent(id_t entityId)
    {
        assert(this->hasComponent<T>(entityId) &&
               "Entity does not have component");
        this->removeComponent(T::getTypeId(), entityId);
    }

    void removeAllComponents(id_t entityId)
    {
        for (const auto &list: this->componentLists_) {
            if (list.second.find(entityId) != list.second.end()) {
                this->removeComponent(list.first, entityId);
            }
        }
    }

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
} // namespace rtype