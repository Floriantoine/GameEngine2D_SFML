#include "system/CollisionColor.hpp"

namespace systems {

void CollisionColor::update(long elapsedTime)
{
    auto array =
        this->componentManager_->getComponentList<components::SolidBlock>();
    for (auto it = array.begin(); it != array.end(); ++it) {
        components::SolidBlock *solidC =
            static_cast<components::SolidBlock *>(it->second);
        components::Color *colorC =
            this->componentManager_->getComponent<components::Color>(it->first);
        if (solidC && colorC) {
            if (solidC->_haveCollision)
                colorC->_color = sf::Color::Red;
            else
                colorC->_color = sf::Color::Blue;
        }
    }
};
} // namespace systems