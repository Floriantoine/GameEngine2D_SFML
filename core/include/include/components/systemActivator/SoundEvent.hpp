#pragma once

#include "Imgui.hpp"
#include "component/Component.hpp"
#include "nlohmann/json.hpp"
#include <SFML/Audio/Sound.hpp>

namespace components {

class SoundEvent : public fa::Component<SoundEvent> {
  public:
    std::string _soundName;
    int _key;
    sf::Sound _sound;
    bool _loop;

  public:
    SoundEvent(std::string soundName, int key, bool loop);
    ~SoundEvent()
    {
        _sound.stop();
    };
    void initSound();
    static void factory(fa::id_t entityId, nlohmann::json config);
    void dislayImGuiPanel() override;
};
} // namespace components