#pragma once

#include <SFML/Graphics/Texture.hpp>

namespace flowEngine {

class Texture {
  private:
    sf::Texture _texture;
    std::string _path;
    std::string _name;

  public:
    Texture(std::string const &path, std::string const &name);
    ~Texture() = default;

    sf::Texture *getSfTexture()
    {
        return &_texture;
    };

    std::string const &getName() const
    {
        return this->_name;
    };

    std::string const getPath() const
    {
        return this->_path;
    };
};

} // namespace flowEngine