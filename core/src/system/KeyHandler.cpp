#include "system/KeyHandler.hpp"
#include "Game.hpp"

namespace systems {
KeyHandler::KeyHandler()
{
    _subject = Subject();
    ObserverManager &observerManager =
        Game::Game::getInstance().getObserverManager();
    observerManager.addSubject(&_subject);

    _observer = Observer{
        [&](KeyPressed const &inf) { _keysPressed.push_back(inf.key); },

    };
    observerManager.addObserver(&_observer);
}
void KeyHandler::update(long elapsedTime)
{
    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        // Check For Key Space
        if (_keysPressed.size() &&
            std::find(_keysPressed.begin(), _keysPressed.end(),
                (int)sf::Keyboard::Space) != _keysPressed.end()) {
            auto array =
                this->_componentManager
                    ->getComponentList<components::PresseSpaceMakeEntity>();
            for (auto &it: array) {
                components::PresseSpaceMakeEntity *comp =
                    static_cast<components::PresseSpaceMakeEntity *>(it.second);
                if (comp == nullptr)
                    continue;
                _subject.CreateMessage(NewEntity{comp->_configPath});
            }
        }

        this->_elapsedTime = 0;
        _keysPressed.clear();
    }
}
} // namespace systems