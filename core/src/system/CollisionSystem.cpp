#include "system/CollisionSystem.hpp"

namespace systems {

void CollisionSystem::update(long elapsedTime)
{
    tools::Chrono::start();
    this->_elapsedtime += elapsedTime;
    if (this->_elapsedtime >= 16) {
        this->_elapsedtime = 0;
        std::vector<collisStruct> _infs;
        collisStruct inf;

        auto array =
            this->componentManager_->getComponentList<components::SolidBlock>();
        if (array.size() <= 1) {
            return;
        }
        for (auto &it: array) {
            components::SolidBlock *solidC =
                static_cast<components::SolidBlock *>(it.second);
            if (solidC == nullptr)
                break;
            components::PosComponent *posC =
                this->componentManager_->getComponent<components::PosComponent>(
                    it.first);
            if (posC) {
                solidC->_haveCollision = false;
                components::Size *sizeC =
                    this->componentManager_->getComponent<components::Size>(
                        it.first);
                inf.id = it.first;
                inf.targetId = &solidC->_targetId;
                inf._floatRect = sf::FloatRect(
                    posC->_pos, sizeC ? sizeC->_size : sf::Vector2f(1, 1));
                inf._haveCollision = &solidC->_haveCollision;
                _infs.push_back(inf);
            }
        }
        for (auto it = _infs.begin(); it != _infs.end(); ++it) {
            for (auto it2 = std::next(it); it2 != _infs.end(); ++it2) {
                if (it->_floatRect.intersects(it2->_floatRect)) {
                    *(it->targetId) = it2->id;
                    *(it2->targetId) = it->id;
                    *(it->_haveCollision) = true;
                    *(it2->_haveCollision) = true;
                }
            }
        }
    }
    tools::Chrono::end("collision System");
}
} // namespace systems