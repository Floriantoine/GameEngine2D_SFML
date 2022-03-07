
#include "components/systemActivator/SoundEvent.hpp"
#include "Game.hpp"

namespace components {
SoundEvent::SoundEvent(std::string soundName, int key, bool loop)
    : _soundName(soundName), _key(key), _loop(loop)
{
    this->initSound();
}

void SoundEvent::initSound()
{
    fa::Sound::SoundBuffer *soundBuf =
        Game::Game::getInstance().getSoundBufferManager().getSoundBufferByName(
            _soundName);
    if (soundBuf != nullptr) {
        sf::SoundBuffer &buff = soundBuf->getSoundBufferRef();
        _sound.setBuffer(buff);
        if (_loop) {
            _sound.setLoop(true);
        }
    }
}

void SoundEvent::factory(id_t entityId, nlohmann::json config)
{
    std::string name = "";
    int key = 0;
    bool loop = false;

    if (config != nullptr && config.type() == nlohmann::json::value_t::object) {
        if (config["soundName"] != nullptr &&
            config["soundName"].type() == nlohmann::json::value_t::string) {
            name = config["soundName"];
        }
        if (config["key"] != nullptr &&
            config["key"].type() == nlohmann::json::value_t::number_unsigned) {
            key = config["key"];
        }
        if (config["loop"] != nullptr &&
            config["loop"].type() == nlohmann::json::value_t::boolean) {
            loop = config["loop"];
        }
    }

    Game::Game::getInstance()
        .getComponentManager()
        .addComponent<components::SoundEvent>(entityId, name, key, loop);
}

void SoundEvent::dislayImGuiPanel()
{
    if (ImGui::CollapsingHeader(
            "SoundEventComponent##ImGuiSoundEventModifier")) {
        static int indexSoundEvent = -1;
        std::vector<char *> array;
        std::vector<std::string> nameList = Game::Game::getInstance()
                                                .getSoundBufferManager()
                                                .getSoundBufferNames();

        // String to char
        array.reserve(nameList.size());
        for (auto &item: nameList) {
            array.push_back(const_cast<char *>(item.c_str()));
        }
        // ---

        // Init indexSoundEvent
        if (indexSoundEvent == -1) {
            auto it =
                std::find(nameList.begin(), nameList.end(), this->_soundName);
            if (it != nameList.end()) {
                indexSoundEvent = std::distance(nameList.begin(), it);
            }
        }
        // ------

        ImGui::ListBox("##ImGuiSoundEventModifierListSoundName",
            &indexSoundEvent, &array[0], array.size());
        if (ImGui::Button("Set Sound##ImGuiSoundEventModifier")) {
            this->_soundName = nameList[indexSoundEvent];
            this->initSound();
        }
        ImGui::InputInt("Key: ##ImGuiSoundEventModifier", &_key);
    }
};
} // namespace components