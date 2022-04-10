#pragma once

#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/System/Clock.hpp>

namespace components {

class EntitySpawner : public fa::Component<EntitySpawner> {
  public:
    enum class SpawnType : int
    {
        NUMBER = 0,
        TIME,
        RANDOM,

    };
    SpawnType _spawnType;
    int _entityNumber;
    int _entityTime;
    std::string _configPath;
    sf::Clock _clock;

    EntitySpawner()
        : _spawnType(SpawnType::NUMBER), _entityNumber(0), _entityTime(1000),
          _configPath(""){};
    EntitySpawner(SpawnType spawnType, int entityNumber, int entityTime,
        std::string configPath)
        : _spawnType(spawnType), _entityNumber(entityNumber),
          _entityTime(entityTime), _configPath(configPath){};
    ~EntitySpawner() = default;

    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components