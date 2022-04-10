#include "system/SpriteSystem.hpp"
#include "Game.hpp"
#include "components/Size.hpp"

namespace systems {

TextureInf::TextureInf(
    sf::Texture texture, std::string name, SpriteType type, int step)
    : _texture(texture), _name(name), _type(type), _step(step){};
TextureInf::TextureInf(sf::Texture texture, std::string name)
    : _texture(texture), _name(name), _type(SpriteType::DEFAULT), _step(1){};

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

TextureInf *SpriteSystem::getTexture(uint64 id)
{
    if (isRegistered(id) == false) {
        return nullptr;
    }
    const auto &it = _texturesMap.find(id);
    if (it == _texturesMap.end())
        return nullptr;
    return &it->second;
}

TextureInf *SpriteSystem::getTexture(const std::string name)
{
    uint64 id = tools::stringToId(name);

    if (isRegistered(id) == false) {
        const auto &it = _texturesMap.find(tools::stringToId("missingTexture"));
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
    uint64 id = tools::stringToId(name);

    if (isRegistered(id) == true) {
        return false;
    }
    sf::Texture texture;
    if (texture.loadFromFile(path))
        _texturesMap[id] = TextureInf(texture, name);
    return true;
}

bool SpriteSystem::createTexture(nlohmann::json config)
{
    if (config["path"] != nullptr && config["name"] != nullptr) {
        std::string name = config["name"];
        uint64 id = tools::stringToId(name);

        if (isRegistered(id) == true) {
            return false;
        }
        sf::Texture texture;
        SpriteType type = SpriteType::DEFAULT;
        int step = 1;
        if (texture.loadFromFile(config["path"])) {
            if (config["type"] != nullptr &&
                config["type"].type() == nlohmann::json::value_t::string) {
                if (config["type"] == "ANIMATED") {
                    type = SpriteType::ANIMATED;
                }
                if (config["type"] == "DEFAULT") {
                    type = SpriteType::DEFAULT;
                }
            }
            if (config["step"] != nullptr &&
                config["step"].type() ==
                    nlohmann::json::value_t::number_unsigned) {
                step = config["step"];
            }
            _texturesMap[id] = TextureInf(texture, name, type, step);
        }
        return true;
    }
    return false;
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
        for (auto config: json["textures"]) {
            if (createTexture(config) == false) {
                std::cout << "createTexture Error: " << config["name"] << " / "
                          << config["path"] << std::endl;
            }
        }
    }
}

void SpriteSystem::updateDirectionsSprite(long elapsedTime)
{
    auto array = this->_componentManager
                     ->getComponentList<components::DirectionSprite>();
    for (auto &it: array) {
        components::DirectionSprite *directionSprite =
            static_cast<components::DirectionSprite *>(it.second);
        components::Direction *directionComp =
            this->_componentManager->getComponent<components::Direction>(
                it.first);
        if (directionSprite != nullptr && directionComp != nullptr) {
            components::Sprite *SpriteC =
                this->_componentManager->getComponent<components::Sprite>(
                    it.first);
            std::string textureDir = "";
            if (directionComp->_direction == directions::LEFT) {
                textureDir = directionSprite->_textureDirections["LEFT"];
            } else if (directionComp->_direction == directions::STATIC) {
                textureDir = directionSprite->_textureDirections["STATIC"];
            } else if (directionComp->_direction == directions::RIGHT) {
                textureDir = directionSprite->_textureDirections["RIGHT"];
            } else if (directionComp->_direction == directions::UP) {
                textureDir = directionSprite->_textureDirections["UP"];
            } else if (directionComp->_direction == directions::DOWN) {
                textureDir = directionSprite->_textureDirections["DOWN"];
            }
            if (textureDir != "" && SpriteC->_textureName != textureDir) {
                SpriteC->_textureName = textureDir;
                SpriteC->_isInit = false;
            }
        }
    }
}

void SpriteSystem::update(long elapsedTime)
{
    tools::Chrono::start();

    this->_elapsedTime += elapsedTime;
    if (this->_elapsedTime >= 16) {
        this->updateDirectionsSprite(elapsedTime);

        sf::RenderWindow *window = Game::Game::getInstance().getWindow();
        auto array =
            this->_componentManager->getComponentList<components::Sprite>();
        for (auto &it: array) {
            components::Sprite *SpriteC =
                static_cast<components::Sprite *>(it.second);
            if (SpriteC != nullptr && !SpriteC->_isInit) {
                components::Size *sizeC =
                    this->_componentManager->getComponent<components::Size>(
                        it.first);
                TextureInf *textureInf =
                    this->getTexture(SpriteC->_textureName);
                if (textureInf != nullptr) {
                    sf::Vector2u textureSize = textureInf->_texture.getSize();
                    SpriteC->_currentStep = 0;
                    SpriteC->_clock.restart();
                    SpriteC->_sprite.setTexture(textureInf->_texture);
                    SpriteC->_sprite.setTextureRect(
                        sf::IntRect(sf::Vector2i(1, 1),
                            sf::Vector2i(textureSize.x, textureSize.y)));
                    SpriteC->_isInit = true;
                    if (sizeC != nullptr) {
                        SpriteC->_sprite.setScale(
                            sizeC->_size /
                            (textureSize / sf::Vector2f(textureInf->_step, 1)));
                    } else {
                        SpriteC->_sprite.setScale(sf::Vector2f(1, 1));
                    }
                    if (textureInf != nullptr &&
                        textureInf->_type == SpriteType::ANIMATED) {
                        SpriteC->_clock.restart();

                        SpriteC->_sprite.setTextureRect(sf::IntRect(
                            sf::Vector2i(0, 0),
                            sf::Vector2i((textureSize.x / textureInf->_step),
                                textureSize.y)));
                    }
                }
            } else if (SpriteC != nullptr) {
                components::PosComponent *PosC =
                    this->_componentManager
                        ->getComponent<components::PosComponent>(it.first);
                if (PosC != nullptr)
                    SpriteC->_sprite.setPosition(PosC->_pos);
                TextureInf *textureInf =
                    this->getTexture(SpriteC->_textureName);
                if (textureInf != nullptr &&
                    textureInf->_type == SpriteType::ANIMATED &&
                    SpriteC->_clock.getElapsedTime().asMilliseconds() >
                        SpriteC->_elapseUpdate) {
                    SpriteC->_clock.restart();
                    sf::Vector2u textureSize =
                        SpriteC->_sprite.getTexture()->getSize();
                    int sizeX = (textureSize.x / textureInf->_step);
                    SpriteC->_sprite.setTextureRect(sf::IntRect(
                        sf::Vector2i(sizeX * SpriteC->_currentStep, 0),
                        sf::Vector2i(sizeX, textureSize.y)));
                    SpriteC->_currentStep += 1;
                    if (SpriteC->_currentStep >= textureInf->_step)
                        SpriteC->_currentStep = 0;
                }

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