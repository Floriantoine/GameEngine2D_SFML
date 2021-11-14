/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Health Component
*/

#pragma once

#include "../component/Component.hpp"
#include "nlohmann/json.hpp"

namespace rtype {

class HealthComponent : public Component<HealthComponent> {
  public:
    int health{1};
    int _initHealth{1};

  public:
    HealthComponent() = default;
    HealthComponent(int health) : health{health}, _initHealth{health}
    {
    }
};
} // namespace rtype