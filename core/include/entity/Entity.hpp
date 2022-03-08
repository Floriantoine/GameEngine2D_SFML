#pragma once

#include "tools/tools.hpp"
#include "types.hpp"

namespace fa {

class Entity {
  private:
    static const id_t getNextId()
    {
        static id_t id = 0;
        return id++;
    }

    id_t _id;
    std::string _name;

  public:
    Entity() : _id{this->getNextId()}, _name(std::to_string(_id))
    {
    }
    Entity(const std::string name) : _id{tools::stringToId(name)}, _name(name)
    {
    }
    ~Entity() = default;

    Entity &operator=(const Entity &copy)
    {
        this->_id = copy.getId();
        return *this;
    }

    const id_t &getId() const
    {
        return this->_id;
    }

    const std::string &getFullName() const
    {
        return _name;
    }

    std::string getName() const
    {
        return _name.substr(0, _name.find("##"));
    }
};

} // namespace fa
