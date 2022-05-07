#pragma once

#include "tools/tools.hpp"
#include "types.hpp"
#include <iostream>

namespace fa {

class Entity {
  private:
    static id_t getNextId()
    {
        static id_t id = 0;
        return id++;
    }

    id_t _id;
    std::string _name = "";

  public:
    Entity();
    Entity(const std::string name);
    ~Entity() = default;

    Entity &operator=(const Entity &copy);
    const id_t &getId() const;
    const std::string &getFullName() const;
    std::string getName() const;
};

} // namespace fa
