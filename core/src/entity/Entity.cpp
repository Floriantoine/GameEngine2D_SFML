#include "entity/Entity.hpp"

namespace fa {
Entity::Entity()
{
    id_t id = this->getNextId();
    this->_name = std::to_string(id);
    this->_id = tools::stringToId(_name);
}
Entity::Entity(const std::string name)
    : _id{tools::stringToId(name)}, _name(name)
{
}

Entity &Entity::operator=(const Entity &copy)
{
    this->_id = copy.getId();
    this->_name = copy.getFullName();
    return *this;
}

const id_t &Entity::getId() const
{
    return _id;
}

const std::string &Entity::getFullName() const
{
    return _name;
}

std::string Entity::getName() const
{
    return _name.substr(0, _name.find("##"));
}
} // namespace fa