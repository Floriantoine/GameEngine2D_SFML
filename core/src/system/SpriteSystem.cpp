#include "system/SpriteSystem.hpp"
#include "Game.hpp"

namespace systems {

uint64 SpriteSystem::nameToId(const char *name, size_t length)
{
    uint64 seed;
    return SpookyHash::Hash64(name, length, seed);
}

uint64 SpriteSystem::nameToId(std::string name)
{
    return nameToId(name.c_str(), name.size());
}

bool SpriteSystem::isRegistered(uint64 Id)
{
    return (_texturesMap.find(Id) != _texturesMap.end());
}

sf::Texture *SpriteSystem::getTexture(uint64 id)
{
    if (isRegistered(id) == false) {
        return nullptr;
    }
    const auto &it = _texturesMap.find(id);
    if (it == _texturesMap.end())
        return nullptr;
    return &it->second;
}

sf::Texture *SpriteSystem::getTexture(const std::string name)
{
    uint64 id = nameToId(name);

    if (isRegistered(id) == false) {
        const auto &it = _texturesMap.find(nameToId("missingTexture"));
        if (it != _texturesMap.end())
            return &it->second;
        return nullptr;
    }
    const auto &it = _texturesMap.find(id);
    if (it == _texturesMap.end())
        return nullptr;
    return &it->second;
}

bool SpriteSystem::createTexture(const std::string name, const std::string path)
{
    uint64 id = nameToId(name);

    if (isRegistered(id) == true) {
        return false;
    }
    sf::Texture texture;
    if (texture.loadFromFile(path))
        _texturesMap[id] = texture;
    return true;
}

SpriteSystem::SpriteSystem(std::string const &filePath)
{
    nlohmann::json json = json::loadJson(filePath);

    if (!createTexture(
            "missingTexture", "../core/resources/MissingTexture.jpeg"))
        throw std::overflow_error("load missingTexture error");

    if (json == nlohmann::json::value_t::discarded || json.is_discarded()) {
        std::cout << "Json Config Error: " << filePath << std::endl;
        return;
    } else if (json["textures"] != NULL) {
        for (auto x: json["textures"]) {
            if (x["path"] != NULL && x["name"] != NULL)
                if (createTexture(x["name"], x["path"]) == false)
                    std::cout << "createTexture Error: " << x["name"] << " / "
                              << x["path"] << std::endl;
        }
    }
}

void SpriteSystem::update(long elapsedTime)
{
    tools::Chrono::start();

    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        sf::RenderWindow *window = Game::Game::getInstance().getWindow();
        auto array =
            this->_componentManager->getComponentList<components::Sprite>();
        for (auto &it: array) {
            components::Sprite *SpriteC =
                static_cast<components::Sprite *>(it.second);
            if (!SpriteC->_isInit) {
                sf::Texture *texture = this->getTexture(SpriteC->_textureName);
                if (texture != nullptr) {
                    SpriteC->_sprite.setTexture(*texture);
                    SpriteC->_isInit = true;
                }
            } else {
                components::PosComponent *PosC =
                    this->_componentManager
                        ->getComponent<components::PosComponent>(it.first);
                // components::Size *SizeC =
                // this->_componentManager->getComponent<components::Size>(
                // it->first);
                if (PosC)
                    SpriteC->_sprite.setPosition(PosC->_pos);
                // if (SizeC)
                // SpriteC->_sprite.scale(SizeC->_size);
                window->draw(SpriteC->_sprite);
            }
        }
        this->_elapsedTime = 0;
    }
    tools::Chrono::end("SpriteSystem");
}

SpriteSystem::~SpriteSystem()
{
}
} // namespace systems