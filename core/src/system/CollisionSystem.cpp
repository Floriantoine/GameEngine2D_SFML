#include "system/CollisionSystem.hpp"

namespace systems {

void CollisionSystem::update(long elapsedTime)
{
    tools::Chrono::start();
    this->_elapsedtime += elapsedTime;
    if (this->_elapsedtime >= 16) {
        this->_elapsedtime = 0;
        std::vector<std::pair<collisStruct, bool *>> _rects;
        collisStruct inf;

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
            if (posC && solidC) {
                solidC->_haveCollision = false;
                components::Size *sizeC =
                    this->componentManager_->getComponent<components::Size>(
                        it->first);
                inf.id = it->first;
                inf.targetId = &solidC->_targetId;
                inf._floatRect = sf::FloatRect(
                    posC->_pos, sizeC ? sizeC->_size : sf::Vector2f(1, 1));
                _rects.push_back(std::pair<collisStruct, bool *>(
                    inf, &solidC->_haveCollision));
            }
        }
        for (auto it = _rects.begin(); it != _rects.end(); ++it) {
            for (auto it2 = std::next(it); it2 != _rects.end(); ++it2) {
                if (it->first._floatRect.intersects(it2->first._floatRect)) {
                    *(it->first.targetId) = it2->first.id;
                    *(it2->first.targetId) = it->first.id;
                    *(it->second) = true;
                    *(it2->second) = true;
                }
            }
        }
    }
    tools::Chrono::end("collision System");
}
} // namespace systems