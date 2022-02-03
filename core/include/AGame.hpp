#pragma once

#include "component/ComponentManager.hpp"
#include "factory/PlayerFactory.hpp"
#include "observer/Observer.hpp"
#include "observer/ObserverManager.hpp"
#include "particle/ParticleManager.hpp"
#include "scene/SceneManager.hpp"
#include "sprite/SpriteManager.hpp"
#include "system/SystemManager.hpp"
#include "texture/TextureManager.hpp"
#include <./EventSystem.hpp>
#include <chrono>

class AGame {
  protected:
    bool isRunning{false};
    double _framerateLimit{60};

    rtype::ComponentManager _componentManager;
    rtype::SystemManager _systemManager;
    SceneManager _sceneManager;
    Game::EventSystem _eventSys;
    ObserverManager _observerManager;
    parallax::ParallaxSystem _parallax;
    flowEngine::TextureManager _textureManager;
    flowEngine::SpriteManager _spriteManager;
    ParticleManager _particleSystem;
    factory::PlayerFactory _playerFactory;

    AGame()
        : _componentManager(), _systemManager(_componentManager),
          _observerManager(), _textureManager(), _spriteManager(),
          _eventSys(_observerManager), _parallax(_observerManager),
          _sceneManager(_parallax, _textureManager),
          _particleSystem(_observerManager, _componentManager, _systemManager),
          _playerFactory(_observerManager, _componentManager, _systemManager)
    {
    }
    virtual ~AGame() = default;

  public:
    parallax::ParallaxSystem &getParallax()
    {
        return this->_parallax;
    }

    ObserverManager &getObserverManager()
    {
        return _observerManager;
    }

    /**
     * Paces the game loop to match [getFrequency] updates per second
     *
     * This method is called in the main loop, and must wait until the next
     * tick
     */
    virtual void wait() = 0;

    /**
     * Resets the clock used to calculate of elapsed time
     */
    virtual void resetClock() = 0;

    /**
     * @returns the number of milliseconds elapsed since last game update
     */
    virtual long getElapsedMillisecond() const = 0;

    /**
     * Get game maximum update rate
     *
     * @returns maximum number of updates per second
     */
    double getFramerateLimit() const
    {
        return this->_framerateLimit;
    }

    /**
     * Get actual game update rate
     *
     * @returns actual number of updates per second
     */
    double getFramerate() const
    {
        long elapsedTime = this->getElapsedMillisecond();

        if (elapsedTime == 0)
            elapsedTime = 1;
        return 1000.0 / static_cast<double>(elapsedTime);
    }

    /**
     * Init and Start Game Loop
     */
    void start()
    {
        this->onInit();
        this->isRunning = true;
        this->onStart();
        long elapsed = 0;

        this->resetClock();
        while (this->isRunning) {
            elapsed = this->getElapsedMillisecond();
            this->resetClock();
            this->onBeforeUpdate();
            this->update(elapsed);
            this->onAfterUpdate();
            this->wait();
        }
    }

    /**
     * Stop Game Loop
     *
     */
    void stop()
    {
        this->isRunning = false;
        this->onStop();
    }

    /**
     * Set game update rate
     *
     * @param limit, new framerate Limit
     */
    void setFramerateLimit(double limit)
    {
        this->_framerateLimit = limit;
    }

  private:
    /**
     * Updates Game
     *
     * @param elapsed, number of milliseconds elapsed since last Game Update
     */
    void update(long elapsed)
    {
        ImGui::Begin("test2");
        this->_particleSystem.update(elapsed);
        this->_parallax.update(elapsed);
        this->_eventSys.update(elapsed);
        ImGui::End();
    }

    /**
     * Method called when the Game instance is created
     */
    virtual void onInit()
    {
        this->_particleSystem.init();
    }

    /**
     * Method called when the game starts
     */
    virtual void onStart()
    {
    }

    /**
     * Method called before each game update
     */
    virtual void onBeforeUpdate()
    {
    }

    /**
     * Method called after each game update
     */
    virtual void onAfterUpdate()
    {
    }

    /**
     * Method called when the game ends
     */
    virtual void onStop()
    {
    }
};
