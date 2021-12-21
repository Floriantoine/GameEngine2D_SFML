
#include "component/ComponentManager.hpp"

namespace rtype {

bool ComponentManager::isComponentTypeRegistered(id_t typeId) const
{
    return (this->_componentLists.find(typeId) != this->_componentLists.end());
}

std::unordered_map<id_t, ComponentBase *> &ComponentManager::getComponentList(
    id_t typeId)
{
    auto it = this->_componentLists.find(typeId);
    if (it == this->_componentLists.end()) {
        assert("Component type not registered");
        this->_componentLists.emplace(typeId, 512);
        it = this->_componentLists.find(typeId);
    }
    return it->second;
}

bool ComponentManager::hasComponent(id_t typeId, id_t entityId)
{
    if (this->isComponentTypeRegistered(typeId) == false)
        return false;
    const auto &list = this->getComponentList(typeId);
    return (list.find(entityId) != list.end());
}

ComponentBase *ComponentManager::getComponent(id_t typeId, id_t entityId)
{
    if (this->isComponentTypeRegistered(typeId) == false)
        return nullptr;
    const auto &list = this->getComponentList(typeId);
    const auto &it = list.find(entityId);
    if (it == list.end())
        return nullptr;
    return it->second;
}

void ComponentManager::removeComponent(id_t typeId, id_t entityId)
{
    this->getComponentList(typeId).erase(entityId);
}

ComponentManager::~ComponentManager()
{
    this->_componentLists.clear();
};

void ComponentManager::clear()
{
    this->_componentLists.clear();
}

int ComponentManager::getComponentCount() const
{
    int count = 0;
    for (auto &it: this->_componentLists) {
        count += it.second.size();
    }
    return count;
}

void ComponentManager::removeAllComponents(id_t entityId)
{
    for (const auto &list: this->_componentLists) {
        if (list.second.find(entityId) != list.second.end()) {
            this->removeComponent(list.first, entityId);
        }
    }
}

void ComponentManager::removeAllComponentsRange(id_t startId, id_t endId)
{
    if (endId < startId)
        assert("Bad Range");
    for (startId; startId < endId; startId++) {
        for (const auto &list: this->_componentLists) {
            if (list.second.find(startId) != list.second.end()) {
                this->removeComponent(list.first, startId);
            }
        }
    }
}

} // namespace rtype