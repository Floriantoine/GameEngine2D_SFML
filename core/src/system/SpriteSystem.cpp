#include "system/SpriteSystem.hpp"
#include "Game.hpp"

namespace systems {

TextureInf::TextureInf(sf::Texture texture, std::string name)
    : _texture(texture), _name(name){};

bool SpriteSystem::isRegistered(uint64 Id)
{
    return (_texturesMap.find(Id) != _texturesMap.end());
}

std::vector<std::string> SpriteSystem::getTexturesName() const
{
    std::vector<std::string> names;
    for (auto &texture: this->_texturesMap) {
        names.push_back(texture.second._name);
    }
    return names;
}

sf::Texture *SpriteSystem::getTexture(uint64 id)
{
    if (isRegistered(id) == false) {
        return nullptr;
    }
    const auto &it = _texturesMap.find(id);
    if (it == _texturesMap.end())
        return nullptr;
    return &it->second._texture;
}

sf::Texture *SpriteSystem::getTexture(const std::string name)
{
    uint64 id = tools::stringToId(name);

    if (isRegistered(id) == false) {
        const auto &it = _texturesMap.find(tools::stringToId("missingTexture"));
        if (it != _texturesMap.end())
            return &it->second._texture;
        return nullptr;
    }
    const auto &it = _texturesMap.find(id);
    if (it == _texturesMap.end())
        return nullptr;
    return &it->second._texture;
}

bool SpriteSystem::createTexture(const std::string name, const std::string path)
{
    uint64 id = tools::stringToId(name);

    if (isRegistered(id) == true) {
        return false;
    }
    sf::Texture texture;
    if (texture.loadFromFile(path))
        _texturesMap[id] = TextureInf(texture, name);
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