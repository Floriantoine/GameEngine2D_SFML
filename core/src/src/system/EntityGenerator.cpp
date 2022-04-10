#include "system/EntityGenerator.hpp"
#include "Game.hpp"

namespace systems {
EntityGenerator::EntityGenerator() : ASystem()
{
    _observer = Observer{
        [&](NewEntity const &entity) {
            _pathList.push_back(entity.configPath);
        },

    };
    Game::Game::getInstance().getObserverManager().addObserver(&_observer);
};

void EntityGenerator::update(long elapsedTime)
{
    for (auto &path: _pathList) {
        Game::Game::getInstance().getEntityFactory().createEntity(path);
    }
    _pathList.clear();
}
} // namespace systems