#pragma once

#include "component/ComponentManager.hpp"
#include "factory/EntityFactory.hpp"
#include "factory/ParticleFactory.hpp"
#include "imgui/ecs/EcsController.hpp"
#include "observer/Observer.hpp"
#include "observer/ObserverManager.hpp"
#include "scene/SceneManager.hpp"
#include "sound/SoundBufferManager.hpp"
#include "sprite/SpriteManager.hpp"
#include "system/SystemManager.hpp"
#include "texture/TextureManager.hpp"
#include <./EventSystem.hpp>
#include <chrono>

class AGame {
  protected:
    bool isRunning{false};
    double _framerateLimit{60};

    fa::ComponentManager _componentManager;
    fa::SystemManager _systemManager;
    ObserverManager _observerManager;
    parallax::ParallaxSystem _parallax;
    fa::TextureManager _textureManager;
    SceneManager _sceneManager;
    Game::EventSystem _eventSys;
    fa::SpriteManager _spriteManager;
    ParticleFactory _particleSystem;
    factory::EntityFactory _entityFactory;
    fa::Sound::SoundBufferManager _soundBufferManager;

    AGame()
        : _componentManager(), _systemManager(_componentManager),
          _observerManager(), _parallax(_observerManager), _textureManager(),
          _sceneManager(_parallax, _textureManager),
          _eventSys(_observerManager), _spriteManager(),
          _particleSystem(_observerManager, _componentManager, _systemManager),
          _entityFactory(_observerManager, _componentManager, _systemManager)
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
        return this->_observerManager;
    }

    fa::ComponentManager &getComponentManager()
    {
        return this->_componentManager;
    }
    fa::Sound::SoundBufferManager &getSoundBufferManager()
    {
        return this->_soundBufferManager;
    }

    fa::SystemManager &getSystemManager()
    {
        return this->_systemManager;
    }
    factory::EntityFactory &getEntityFactory()
    {
        return this->_entityFactory;
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
        this->_eventSys.update(elapsed);

        this->_particleSystem.update(elapsed);
        this->_parallax.update(elapsed);

        imguiTools::EcsController::update(elapsed);
        tools::Chrono::display();
    }

    /**
     * Method called when the Game instance is created
     */
    virtual void onInit()
    {
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
