#include "system/CollisionColor.hpp"
#include "components/Color.hpp"
#include "components/SolidBlock.hpp"

namespace systems {

void CollisionColor::update(long elapsedTime)
{
    auto array =
        this->_componentManager->getComponentList<components::SolidBlock>();
    for (auto &it: array) {
        components::SolidBlock *solidC =
            static_cast<components::SolidBlock *>(it.second);
        components::Color *colorC =
            this->_componentManager->getComponent<components::Color>(it.first);
        if (solidC && colorC) {
            if (solidC->_haveCollision)
                colorC->_color = sf::Color::Red;
            else
                colorC->_color = sf::Color::Blue;
        }
    }
};
} // namespace systems