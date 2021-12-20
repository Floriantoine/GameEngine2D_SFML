/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** System manager class
*/

#pragma once

#include "../assert.hpp"
#include "../types.hpp"
#include "ASystem.hpp"
#include "component/ComponentManager.hpp"

#include <memory>
#include <unordered_map>

namespace rtype {
class SystemManager {
  private:
    ComponentManager &componentManager_;
    std::unordered_multimap<ASystem::system_group_e, std::shared_ptr<ASystem>>
        systemList_;

  public:
    SystemManager(ComponentManager &componentManager)
        : componentManager_{componentManager}
    {
    }
    SystemManager(const SystemManager &) = delete;
    SystemManager(SystemManager &&) = delete;
    ~SystemManager() = default;

    SystemManager &operator=(const SystemManager &) = delete;

    void update(long elapsedTime)
    {
        for (const auto &system: this->systemList_) {
            system.second->update(elapsedTime);
        }
    }

    void clear()
    {
        this->systemList_.clear();
    }

    void update(ASystem::system_group_e group, long elapsedTime)
    {
        auto range = this->systemList_.equal_range(group);

        for (auto it = range.first; it != range.second; ++it) {
            it->second->update(elapsedTime);
        }
    }

    template <class T, typename... Args>
    std::shared_ptr<T> createSystem(Args &&...args)
    {
        STATIC_ASSERT_IS_SYSTEM(T);
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        system->componentManager_ = &this->componentManager_;
        this->systemList_.emplace(std::make_pair(system->getGroup(), system));
        return system;
    }

    template <class T> void removeSystem(std::shared_ptr<T> system)
    {
        STATIC_ASSERT_IS_SYSTEM(T);
        for (auto it = this->systemList_.cbegin();
             it != this->systemList_.cend(); ++it) {
            if (it->second == system) {
                this->systemList_.erase(it);
                return;
            }
        }
        assert("System is not registered in this SystemManager instance");
    }
};
} // namespace rtype
