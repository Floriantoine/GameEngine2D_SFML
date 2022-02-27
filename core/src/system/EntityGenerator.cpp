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
        nlohmann::json _json = json::loadJson(path);

        if (_json == nlohmann::json::value_t::discarded ||
            _json.is_discarded()) {
            std::cout << "Json Config Error: " << path << std::endl;
        } else {
            for (auto it = _json.begin(); it != _json.end(); ++it) {
                if (_componentManager->componentNameIsRegister(it.key())) {
                    _componentManager->addComponent(
                        it.key(), 30000, it.value());
                } else {
                    std::cout << "Component: " << it.key() << " undefined"
                              << std::endl;
                }
            }
        }
    }
    _pathList.clear();
}
} // namespace systems