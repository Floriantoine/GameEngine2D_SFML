#include "system/DiesLeavesScreen.hpp"
#include "Game.hpp"

namespace systems {
void DiesLeavesScreen::update(long elapsedTime)
{
    tools::Chrono::start();

    this->_elapsedtime += elapsedTime;
    if (this->_elapsedtime >= 16) {
        auto array = this->componentManager_
                         ->getComponentList<components::DiesLeavesScreen>();
        for (auto &it: array) {
            components::DiesLeavesScreen *diesLeavesScreenC =
                static_cast<components::DiesLeavesScreen *>(it.second);
            if (diesLeavesScreenC == nullptr)
                break;
            components::PosComponent *PosC =
                this->componentManager_->getComponent<components::PosComponent>(
                    it.first);
            if (PosC == nullptr) {
                break;
            }
            if (PosC->_pos.x < 0 || PosC->_pos.y < 0) {
                // Kill Entity
                this->componentManager_->removeAllComponents(it.first);
            } else {
                sf::Vector2u windowSize =
                    Game::Game::getInstance().getWindow()->getSize();
                if (PosC->_pos.x > windowSize.x ||
                    PosC->_pos.y > windowSize.y) {
                    // kill entity
                    this->componentManager_->removeAllComponents(it.first);
                }
            }
        }
        this->_elapsedtime = 0;
    }
    tools::Chrono::end("DiesLeavesScreenSystem");
}
} // namespace systems