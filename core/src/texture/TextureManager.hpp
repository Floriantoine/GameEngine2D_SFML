#pragma once

#include "Texture.hpp"

namespace flowEngine {

class TextureManager {
  private:
    std::vector<Texture> _textures;

  public:
    TextureManager(/* args */);
    ~TextureManager();
    void createTexture(std::string const &path, std::string const &name);
    void deleteTexture(std::string const &name);
    Texture &getTextureByName(std::string const &name);
};

} // namespace flowEngine
