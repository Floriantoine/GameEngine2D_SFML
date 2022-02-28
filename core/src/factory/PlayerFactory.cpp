#include "factory/PlayerFactory.hpp"

namespace factory {

PlayerFactory::PlayerFactory(ObserverManager &observerManager,
    rtype::ComponentManager &componentManager,
    rtype::SystemManager &systemManager)
    : _observerManager(observerManager), _componentManager(componentManager),
      _systemManager(systemManager)
{
}

void PlayerFactory::createPlayer(std::string path, int id)
{
    nlohmann::json _json = json::loadJson(path);

    if (_json == nlohmann::json::value_t::discarded || _json.is_discarded()) {
        std::cout << "Json Config Error: " << path << std::endl;
    } else {
        for (auto it = _json.begin(); it != _json.end(); ++it) {
            if (this->_componentManager.componentNameIsRegister(it.key())) {
                this->_componentManager.addComponent(it.key(), id, it.value());
            } else {
                std::cout << "Component: " << it.key() << " undefined"
                          << std::endl;
            }
        }
    }
}

void PlayerFactory::init()
{
    this->createPlayer("../core/json/entity/Player.json", 20000);
    this->createPlayer("../core/json/entity/Enemy.json", 20001);
    this->createPlayer("../core/json/entity/Protector.json", 20002);
}

PlayerFactory::~PlayerFactory()
{
}

}; // namespace factory