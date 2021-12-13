/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Component base class
*/

#pragma once

#include "../types.hpp"

namespace rtype {

class Entity;

class ComponentBase {
    friend class ComponentManager;

  protected:
    Entity *entity_{nullptr};

    static id_t getNextTypeId()
    {
        static id_t id = 0;
        return id++;
    }

  public:
    Entity *getEntity() const
    {
        return this->entity_;
    }
};

} // namespace rtype
