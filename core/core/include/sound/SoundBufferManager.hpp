#pragma once

#include "sound/SoundBuffer.hpp"
#include <algorithm>
#include <string>
#include <vector>

namespace fa {
namespace Sound {

class SoundBufferManager {
  private:
    std::vector<SoundBuffer> _soundsBuffer;

  public:
    SoundBufferManager(/* args */);
    ~SoundBufferManager();
    void createSoundBuffer(std::string const &path, std::string const &name);
    void deleteSoundBuffer(std::string const &name);
    SoundBuffer *getSoundBufferByName(std::string const &name);
    std::vector<SoundBuffer> getSoundBufferList() const;
    std::vector<std::string> getSoundBufferNames() const;
};

} // namespace Sound
} // namespace fa
