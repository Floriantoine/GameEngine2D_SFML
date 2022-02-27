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

    // -----------------------------------------------------------------------------------------------------------------------------
    // registerComponent Part
    // -----------------------------------------------------------------------------------------------------------------------------
    _componentManager.registerComponentName(
        "Color", components::Color::factory);
    _componentManager.registerComponentName(
        "Damage", components::Damage::factory);
    _componentManager.registerComponentName(
        "DiesLeavesScreen", components::DiesLeavesScreen::factory);
    _componentManager.registerComponentName(
        "Force", components::ForceComponent::factory);
    _componentManager.registerComponentName(
        "Gravity", components::Gravity::factory);
    _componentManager.registerComponentName(
        "Health", components::HealthComponent::factory);
    _componentManager.registerComponentName(
        "KeyMovement", components::KeyMovement::factory);
    _componentManager.registerComponentName(
        "LifeTime", components::LifeTime::factory);
    _componentManager.registerComponentName(
        "LoopLife", components::LoopLife::factory);
    _componentManager.registerComponentName(
        "Masse", components::MasseComponent::factory);
    _componentManager.registerComponentName(
        "MouseForce", components::MouseForce::factory);
    _componentManager.registerComponentName(
        "ParticleIdentity", components::ParticleIdentity::factory);
    _componentManager.registerComponentName(
        "Pos", components::PosComponent::factory);
    _componentManager.registerComponentName(
        "RectangleShape", components::RectangleShape::factory);
    _componentManager.registerComponentName("Size", components::Size::factory);
    _componentManager.registerComponentName(
        "isSolidBlock", components::SolidBlock::factory);
    _componentManager.registerComponentName(
        "SpawnMousePos", components::SpawnMousePos::factory);
    _componentManager.registerComponentName(
        "SpawnPos", components::SpawnPos::factory);
    _componentManager.registerComponentName(
        "Sprite", components::Sprite::factory);
    _componentManager.registerComponentName(
        "LinearMovement", components::LinearMovement::factory);
    _componentManager.registerComponentName(
        "PresseSpaceMakeEntity", components::PresseSpaceMakeEntity::factory);
    _componentManager.registerComponentName(
        "HaveCollisionDamage", components::HaveCollisionDamage::factory);
    _componentManager.registerComponentName(
        "TargetEntity", components::TargetEntity::factory);
    // -----------------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------------

    // -----------------------------------------------------------------------------------------------------------------------------
    // _systemManager.createSystem<SystemType>();
    // -----------------------------------------------------------------------------------------------------------------------------
    _systemManager.createSystem<systems::SpriteSystem>(
        "../core/json/SpriteSystem.json");
    _systemManager.createSystem<rtype::ParticleMousePosSystem>(
        _observerManager);
    _systemManager.createSystem<rtype::ParticleTimeLifeSystem>();
    _systemManager.createSystem<systems::KeyMovement>();
    _systemManager.createSystem<systems::ParticlesSystem>();
    _systemManager.createSystem<systems::CollisionSystem>();
    _systemManager.createSystem<systems::DisplayShape>();
    _systemManager.createSystem<systems::CollisionColor>();
    _systemManager.createSystem<systems::GravitySystem>();
    _systemManager.createSystem<systems::DiesLeavesScreen>();
    _systemManager.createSystem<systems::CollisionDamage>();
    _systemManager.createSystem<systems::HealthSystem>();
    _systemManager.createSystem<systems::MovementSystem>();
    _systemManager.createSystem<systems::EntityGenerator>();
    _systemManager.createSystem<systems::KeyHandler>();
    _systemManager.createSystem<rtype::MouseForceSystem>(_observerManager);
    // -----------------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------------

    ImPlot::CreateContext();
    ImGui::SFML::Init(*this->_window);

    _playerFactory.init();
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
    ImPlot::DestroyContext();
}

} // namespace Game