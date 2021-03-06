
#pragma once

#include "./Singleton.hpp"
#include "AGame.hpp"
#include "factory/ParticleFactory.hpp"
#include "parallax/ParallaxSystem.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window.hpp>
#include <thread>

namespace Game {

class Game : public AGame, public Singleton<Game> {
  private:
    std::unique_ptr<sf::RenderWindow> _window;
    sf::VideoMode _videoMode{1920, 1080};
    sf::Uint32 _windowStyle{sf::Style::Default};
    std::string _windowTitle{"Game Engine"};
    std::chrono::steady_clock::time_point _lastUpdate;
    sf::Clock _imguiClock;

  public:
    std::shared_ptr<systems::SpriteSystem> _spiteSystem;

    void setWindowTitle(const std::string &title);
    void setVideoMode(sf::VideoMode mode);
    void setWindowStyle(sf::Uint32 style);
    sf::RenderWindow *getWindow() const;
    void onInit() override;
    void onBeforeUpdate() override;
    void onAfterUpdate() override;

    void resetClock() override;
    long getElapsedMillisecond() const override;
    void wait() override;

    Game();
    ~Game();
};

} // namespace Game