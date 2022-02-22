
#include "components/particle/ParticleIdentityComponent.hpp"
#include "Game.hpp"

namespace components {
void ParticleIdentity::factory(id_t entityId, nlohmann::json config)
{
    sf::PrimitiveType type = sf::PrimitiveType::Points;

    if (config == "quads")
        type = sf::PrimitiveType::Quads;
    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::ParticleIdentity>(entityId, type);
}
} // namespace components