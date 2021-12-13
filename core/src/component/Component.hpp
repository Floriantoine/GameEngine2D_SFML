/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Component class
*/

#pragma once

#include "./ComponentBase.hpp"

namespace rtype {

template <typename T> class Component : public ComponentBase {
  public:
    static id_t getTypeId()
    {
        static id_t id = ComponentBase::getNextTypeId();
        return id;
    }
};

} // namespace rtype
