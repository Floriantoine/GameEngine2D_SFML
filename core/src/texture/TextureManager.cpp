
#include "TextureManager.hpp"

namespace flowEngine {

void TextureManager::createTexture(
    std::string const &path, std::string const &name)
{
    this->_textures.push_back(Texture(path, name));
}

void TextureManager::deleteTexture(std::string const &name)
{
    auto iter = std::find_if(this->_textures.begin(), this->_textures.end(),
        [&](Texture const &texture) { return texture.getName() == name; });

    if (iter != this->_textures.end()) {
        this->_textures.erase(iter);
    }
}

Texture &TextureManager::getTextureByName(std::string const &name)
{
    auto iter = std::find_if(this->_textures.begin(), this->_textures.end(),
        [&](Texture const &texture) { return texture.getName() == name; });

    if (iter != this->_textures.end()) {
        return *iter;
    } else {
        // Need Throw !
    }
    return *iter;
}

TextureManager::TextureManager(/* args */)
{
}

TextureManager::~TextureManager()
{
}

} // namespace flowEngine
