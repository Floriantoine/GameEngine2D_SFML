#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "observer/Observer.hpp"

namespace systems {

class EntityGenerator : public rtype::ASystem {
  public:
    Observer _observer;
    std::vector<std::string> _pathList;

    EntityGenerator();
    ~EntityGenerator() = default;

    void update(long elapsedTime) override;
};
} // namespace systems