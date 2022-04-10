#include "sound/SoundBuffer.hpp"
#include <iostream>

namespace fa {

namespace Sound {

SoundBuffer::SoundBuffer(std::string const &path, std::string const &name)
{
    if (this->_soundBuffer.loadFromFile(path)) {
        this->_path = path;
        this->_name = name;
    } else {
        this->_soundBuffer.loadFromFile("../core/resources/error.jpeg");
        this->_path = "";
        this->_name = name;
        std::cout << "path Error, Load error Sound Buffer, [" << name << "]["
                  << path << "]" << std::endl;
    }
}

} // namespace Sound
} // namespace fa