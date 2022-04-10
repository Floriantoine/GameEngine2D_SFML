#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

namespace fa {
namespace Sound {

class SoundBuffer {
  private:
    sf::SoundBuffer _soundBuffer;
    std::string _path;
    std::string _name;

  public:
    SoundBuffer(std::string const &path, std::string const &name);
    ~SoundBuffer() = default;

    sf::SoundBuffer *getSoundBuffer()
    {
        return &_soundBuffer;
    };

    sf::SoundBuffer &getSoundBufferRef()
    {
        return _soundBuffer;
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

} // namespace Sound
} // namespace fa