#include "system/DisplayShape.hpp"
#include "Game.hpp"
#include "components/Color.hpp"
#include "components/PosComponent.hpp"
#include "components/RectangleShape.hpp"
#include "components/Size.hpp"
#include "components/hud/Text.hpp"

namespace systems {

void DisplayShape::update(long elapsedTime)
{
    auto array =
        this->_componentManager->getComponentList<components::RectangleShape>();
    for (auto &it: array) {
        components::RectangleShape *rectShapeC =
            static_cast<components::RectangleShape *>(it.second);
        components::PosComponent *posC =
            this->_componentManager->getComponent<components::PosComponent>(
                it.first);
        if (!posC || !rectShapeC)
            continue;
        components::Size *sizeC =
            this->_componentManager->getComponent<components::Size>(it.first);
        components::Color *colorC =
            this->_componentManager->getComponent<components::Color>(it.first);
        rectShapeC->_shape.setSize(sizeC ? sizeC->_size : sf::Vector2f(1, 1));
        rectShapeC->_shape.setOutlineThickness(rectShapeC->_thickness);
        rectShapeC->_shape.setFillColor(
            colorC ? colorC->_color : sf::Color::White);
        rectShapeC->_shape.setPosition(posC->_pos);

        Game::Game::getInstance().getWindow()->draw(rectShapeC->_shape);
    }

    // ------------------------------------------
    // ------------------------------------------
    // ------------------------------------------
    array = this->_componentManager->getComponentList<components::Text>();
    for (auto &it: array) {
        components::Text *textC = static_cast<components::Text *>(it.second);
        components::PosComponent *posC =
            this->_componentManager->getComponent<components::PosComponent>(
                it.first);
        if (!textC || !posC)
            continue;
        textC->_text.setPosition(posC->_pos);
        Game::Game::getInstance().getWindow()->draw(textC->_text);
    }
}
} // namespace systems