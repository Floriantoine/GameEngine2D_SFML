#include "factory/PlayerFactory.hpp"

namespace factory {

PlayerFactory::PlayerFactory(ObserverManager &observerManager,
    rtype::ComponentManager &componentManager,
    rtype::SystemManager &systemManager)
    : _observerManager(observerManager), _componentManager(componentManager),
      _systemManager(systemManager)
{
    int arrayPos[2] = {200, 400};
    _componentManager.addComponent<components::PosComponent>(10000, arrayPos);
    _componentManager.addComponent<components::Color>(10000, sf::Color::Blue);
    _componentManager.addComponent<components::SolidBlock>(10000);
    _componentManager.addComponent<components::RectangleShape>(10000);
    _componentManager.addComponent<components::KeyMovement>(10000);

    arrayPos[0] = 220;
    _componentManager.addComponent<components::PosComponent>(10001, arrayPos);
    _componentManager.addComponent<components::Color>(10001, sf::Color::Blue);
    _componentManager.addComponent<components::SolidBlock>(10001);
    _componentManager.addComponent<components::RectangleShape>(10001);
}

PlayerFactory::~PlayerFactory()
{
}

}; // namespace factory