#include "texture/Texture.hpp"
#include <iostream>

namespace fa {

Texture::Texture(std::string const &path, std::string const &name)
{
    if (this->_texture.loadFromFile(path)) {
        this->_path = path;
        this->_name = name;
    } else if (this->_texture.loadFromFile("../core/resources/error.jpeg")) {
        this->_path = "../core/resources/error.jpeg";
        this->_name = name;
        std::cout << "path Error, Load error texture, [" << name << "][" << path
                  << "]" << std::endl;
    }
}

} // namespace fa