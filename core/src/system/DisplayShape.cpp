#include "system/DisplayShape.hpp"
#include "Game.hpp"

namespace systems {

void DisplayShape::update(long elapsedTime)
{
    auto array =
        this->componentManager_->getComponentList<components::RectangleShape>();
    for (auto &it: array) {
        components::RectangleShape *rectShapeC =
            static_cast<components::RectangleShape *>(it.second);
        components::PosComponent *posC =
            this->componentManager_->getComponent<components::PosComponent>(
                it.first);
        components::Color *colorC =
            this->componentManager_->getComponent<components::Color>(it.first);
        if (!posC || !rectShapeC)
            return;
        rectShapeC->_shape.setSize(rectShapeC->_size);
        rectShapeC->_shape.setOutlineThickness(rectShapeC->_thickness);
        rectShapeC->_shape.setFillColor(
            colorC ? colorC->_color : sf::Color::White);
        rectShapeC->_shape.setPosition(posC->_pos);

        Game::Game::getInstance().getWindow()->draw(rectShapeC->_shape);
    }
}
} // namespace systems