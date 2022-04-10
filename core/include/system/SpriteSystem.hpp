#pragma once

#include "ASystem.hpp"
#include "Components.hpp"
#include "nlohmann/json.hpp"
#include "tools/Spooky.hpp"
#include "tools/jsonTools.hpp"
#include "tools/tools.hpp"
namespace systems {

class TextureInf {
  public:
    sf::Texture _texture;
    std::string _name;
    TextureInf(sf::Texture texture, std::string name);
    TextureInf() = default;
};
class SpriteSystem : public fa::ASystem {
  private:
    std::unordered_map<uint64, TextureInf> _texturesMap;
    long _elapsedTime = 0;

  public:
    SpriteSystem(std::string const &filePath);
    ~SpriteSystem();

    sf::Texture *getTexture(uint64 Id);
    sf::Texture *getTexture(const std::string name);
    std::vector<std::string> getTexturesName() const;

    bool createTexture(const std::string name, const std::string path);
    bool isRegistered(uint64 Id);
    void update(long elapsedTime) override;
};
} // namespace systems
