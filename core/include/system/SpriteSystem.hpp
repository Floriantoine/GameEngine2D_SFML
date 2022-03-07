#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "nlohmann/json.hpp"
#include "tools/Spooky.hpp"
#include "tools/jsonTools.hpp"
namespace systems {

class SpriteSystem : public fa::ASystem {
  private:
    std::unordered_map<uint64, sf::Texture> _texturesMap;
    long _elapsedTime = 0;

  public:
    SpriteSystem(std::string const &filePath);
    ~SpriteSystem();
    sf::Texture *getTexture(uint64 Id);
    sf::Texture *getTexture(const std::string name);
    bool createTexture(const std::string name, const std::string path);
    bool isRegistered(uint64 Id);
    uint64 nameToId(std::string name);
    uint64 nameToId(const char *name, size_t length);
    void update(long elapsedTime) override;
};
} // namespace systems
