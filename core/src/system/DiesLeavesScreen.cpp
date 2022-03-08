#include "system/DiesLeavesScreen.hpp"
#include "Game.hpp"
#include "components/PosComponent.hpp"

namespace systems {
void DiesLeavesScreen::update(long elapsedTime)
{
    tools::Chrono::start();

    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        auto array = this->_componentManager
                         ->getComponentList<components::DiesLeavesScreen>();
        for (auto &it: array) {
            components::DiesLeavesScreen *diesLeavesScreenC =
                static_cast<components::DiesLeavesScreen *>(it.second);
            if (diesLeavesScreenC == nullptr)
                continue;
            components::PosComponent *PosC =
                this->_componentManager->getComponent<components::PosComponent>(
                    it.first);
            if (PosC == nullptr) {
                continue;
            }
            if (PosC->_pos.x < 0 || PosC->_pos.y < 0) {
                // Kill Entity
                Game::Game::getInstance().getEntityFactory().destroyEntity(
                    it.first);
            } else {
                sf::Vector2u windowSize =
                    Game::Game::getInstance().getWindow()->getSize();
                if (PosC->_pos.x > windowSize.x ||
                    PosC->_pos.y > windowSize.y) {
                    // kill entity
                    Game::Game::getInstance().getEntityFactory().destroyEntity(
                        it.first);
                }
            }
        }
        this->_elapsedTime = 0;
    }
    tools::Chrono::end("DiesLeavesScreenSystem");
}
} // namespace systems