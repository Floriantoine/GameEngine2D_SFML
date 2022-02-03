#include "./Game.hpp"
#include "imgui.h"
#include <imgui-SFML.h>
#include <stdio.h>

int Observer::static_number_ = 0;

int main(int argc, char const *argv[])
{
    Game::Game::getInstance().start();
    return 0;
}

namespace Game {

void Game::resetClock()
{
    this->_lastUpdate = std::chrono::steady_clock::now();
}

long Game::getElapsedMillisecond() const
{
    const auto &elapsed = std::chrono::steady_clock::now() - this->_lastUpdate;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
        .count();
}

void Game::wait()
{
    auto interval =
        std::chrono::milliseconds((long)(1000 / this->getFramerateLimit()));
    const auto &now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::milliseconds(this->getElapsedMillisecond());
    std::this_thread::sleep_until(now - elapsed + interval);
}

void Game::setWindowTitle(const std::string &title)
{
    this->_windowTitle = title;
}

void Game::setVideoMode(sf::VideoMode mode)
{
    this->_videoMode = mode;
}

void Game::setWindowStyle(sf::Uint32 style)
{
    this->_windowStyle = style;
}

sf::RenderWindow *Game::getWindow() const
{
    return this->_window.get();
}

void Game::onInit()
{
    this->_window = std::make_unique<sf::RenderWindow>(
        this->_videoMode, this->_windowTitle, this->_windowStyle);

    this->_parallax.setRenderWindow(this->_window.get());
    this->_parallax.clear();
    this->_sceneManager.loadScene("../core/json/scene1.json");

    // _systemManager.createSystem<systems::FormSystem>();
    _systemManager.createSystem<rtype::ParticleMousePosSystem>(
        Game::Game::getInstance().getObserverManager());
    _systemManager.createSystem<rtype::ParticleTimeLifeSystem>();
    _systemManager.createSystem<systems::KeyMovement>();
    _systemManager.createSystem<systems::ParticlesSystem>();
    _systemManager.createSystem<systems::CollisionSystem>();
    _systemManager.createSystem<systems::DisplayShape>();
    _systemManager.createSystem<systems::CollisionColor>();

    ImGui::SFML::Init(*this->_window);
    // Start Test Zone Temporary
    // auto texture =
    //     this->_textureManager.getTextureByName("texture2").getSfTexture();
    // this->_spriteManager.createSprite(texture);
    // this->_dynaS.setSprite(&this->_spriteManager.getSprites()[0]);
    // End  Test Zone Temporary
}

void Game::onBeforeUpdate()
{
    this->_window->clear();
    ImGui::SFML::Update(*this->_window, this->_imguiClock.restart());
}

void Game::onAfterUpdate()
{
    this->_parallax.display();
    this->_spriteManager.display();
    this->_particleSystem.display();
    ImGui::SFML::Render(*this->_window);
    this->_window->display();
}

Game::Game()
{
}

Game::~Game()
{
    ImGui::SFML::Shutdown();
}

} // namespace Game