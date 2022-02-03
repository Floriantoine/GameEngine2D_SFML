#include "system/CollisionSystem.hpp"

namespace systems {

void CollisionSystem::update(long elapsedTime)
{
    this->_elapsedtime += elapsedTime;
    if (this->_elapsedtime >= 16) {
        this->_elapsedtime = 0;
        std::vector<std::pair<sf::FloatRect, bool *>> _rects;

        auto array =
            this->componentManager_->getComponentList<components::SolidBlock>();
        if (array.size() <= 1) {
            return;
        }
        for (auto it = array.begin(); it != array.end(); ++it) {
            components::SolidBlock *solidC =
                static_cast<components::SolidBlock *>(it->second);
            components::PosComponent *posC =
                this->componentManager_->getComponent<components::PosComponent>(
                    it->first);
            if (!posC || !solidC)
                break;
            solidC->_haveCollision = false;
            _rects.push_back(std::pair<sf::FloatRect, bool *>(
                sf::FloatRect(posC->_pos, sf::Vector2f(10, 10)),
                &solidC->_haveCollision));

            // components::Size *sizeC =
            //     this->componentManager_->getComponent<components::Size>(
            //         it->first);
        }
        for (auto it = _rects.begin(); it != _rects.end(); ++it) {
            for (auto it2 = std::next(it); it2 != _rects.end(); ++it2) {
                if (it->first.intersects(it2->first)) {
                    *(it->second) = true;
                    *(it2->second) = true;
                }
            }
        }
    }
}
} // namespace systems