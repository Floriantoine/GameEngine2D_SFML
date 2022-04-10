
#include "sound/SoundBufferManager.hpp"

namespace fa {
namespace Sound {

std::vector<SoundBuffer> SoundBufferManager::getSoundBufferList() const
{
    return this->_soundsBuffer;
}
std::vector<std::string> SoundBufferManager::getSoundBufferNames() const
{
    std::vector<std::string> nameList;

    for (auto &item: this->_soundsBuffer) {
        nameList.push_back(item.getName());
    }
    return nameList;
}

void SoundBufferManager::createSoundBuffer(
    std::string const &path, std::string const &name)
{
    this->_soundsBuffer.push_back(SoundBuffer(path, name));
}

void SoundBufferManager::deleteSoundBuffer(std::string const &name)
{
    auto iter = std::find_if(this->_soundsBuffer.begin(),
        this->_soundsBuffer.end(), [&](SoundBuffer const &soundBuff) {
            return soundBuff.getName() == name;
        });

    if (iter != this->_soundsBuffer.end()) {
        this->_soundsBuffer.erase(iter);
    }
}

SoundBuffer *SoundBufferManager::getSoundBufferByName(std::string const &name)
{
    auto iter = std::find_if(this->_soundsBuffer.begin(),
        this->_soundsBuffer.end(),
        [&](SoundBuffer const &texture) { return texture.getName() == name; });

    if (iter != this->_soundsBuffer.end()) {
        return &(*iter);
    } else {
        // Need Throw !
    }
    return nullptr;
}

SoundBufferManager::SoundBufferManager(/* args */)
{
}

SoundBufferManager::~SoundBufferManager()
{
}

} // namespace Sound
} // namespace fa