#include "system/CollisionSystem.hpp"
#include "components/PosComponent.hpp"
#include "components/Size.hpp"
#include "components/SolidBlock.hpp"
#include "tools/Chrono.hpp"

namespace systems {

void CollisionSystem::update(long elapsedTime)
{
    tools::Chrono::start();
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        this->_elapsedTime = 0;
        std::vector<collisStruct> _infs;
        collisStruct inf;

        auto array =
            this->_componentManager->getComponentList<components::SolidBlock>();
        if (array.size() <= 1) {
            return;
        }
        for (auto &it: array) {
            components::SolidBlock *solidC =
                static_cast<components::SolidBlock *>(it.second);
            if (solidC == nullptr)
                continue;
            components::PosComponent *posC =
                this->_componentManager->getComponent<components::PosComponent>(
                    it.first);
            if (posC) {
                solidC->_haveCollision = false;
                components::Size *sizeC =
                    this->_componentManager->getComponent<components::Size>(
                        it.first);
                inf.id = it.first;
                solidC->_targetsId.clear();
                inf.targetsId = &solidC->_targetsId;
                inf._floatRect = sf::FloatRect(
                    posC->_pos, sizeC ? sizeC->_size : sf::Vector2f(1, 1));
                inf._haveCollision = &solidC->_haveCollision;
                _infs.push_back(inf);
            }
        }
        for (auto it = _infs.begin(); it != _infs.end(); ++it) {
            for (auto it2 = std::next(it); it2 != _infs.end(); ++it2) {
                if (it->_floatRect.intersects(it2->_floatRect)) {
                    it->targetsId->push_back(it2->id);
                    it2->targetsId->push_back(it->id);
                    *(it->_haveCollision) = true;
                    *(it2->_haveCollision) = true;
                }
            }
        }
    }
    tools::Chrono::end("collision System");
}
} // namespace systems