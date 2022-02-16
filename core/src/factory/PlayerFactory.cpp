#include "factory/PlayerFactory.hpp"

namespace factory {

PlayerFactory::PlayerFactory(ObserverManager &observerManager,
    rtype::ComponentManager &componentManager,
    rtype::SystemManager &systemManager)
    : _observerManager(observerManager), _componentManager(componentManager),
      _systemManager(systemManager)
{
    _componentManager.addComponent<components::PosComponent>(
        20000, sf::Vector2f(200, 400));
    // _componentManager.addComponent<components::Color>(20000,
    // sf::Color::Blue);
    _componentManager.addComponent<components::SolidBlock>(20000);
    // _componentManager.addComponent<components::RectangleShape>(20000);
    _componentManager.addComponent<components::KeyMovement>(20000);
    _componentManager.addComponent<components::Sprite>(20000, "texture1");
    _componentManager.addComponent<components::Size>(
        20000, sf::Vector2f(10, 10));

    _componentManager.addComponent<components::PosComponent>(
        20001, sf::Vector2f(220, 400));
    _componentManager.addComponent<components::Color>(20001, sf::Color::Blue);
    _componentManager.addComponent<components::SolidBlock>(20001);
    _componentManager.addComponent<components::RectangleShape>(20001);
    _componentManager.addComponent<components::Size>(
        20001, sf::Vector2f(10, 10));
}

PlayerFactory::~PlayerFactory()
{
}

}; // namespace factory