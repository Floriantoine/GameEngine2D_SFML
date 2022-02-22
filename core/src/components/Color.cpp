
#include "components/Color.hpp"
#include "Game.hpp"

namespace components {
void Color::factory(id_t entityId, nlohmann::json config)
{
    sf::Color color = sf::Color::White;

    if (config == "red") {
        color = sf::Color::Red;
    }
    if (config == "blue") {
        color = sf::Color::Blue;
    }
    if (config == "green") {
        color = sf::Color::Green;
    }
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::Color>(entityId, color);
}
} // namespace components