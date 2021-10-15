#pragma once

#include "./observer/Observer.hpp"
#include <./EventSystem.hpp>
#include <chrono>

class AGame {
  private:
    bool isRunning{false};
    double _framerateLimit{60};
    Game::EventSystem _eventSys;
    Observer *_observer;

  protected:
    parallax::ParallaxSystem _parallax;
    AGame() : _eventSys()
    {
        _observer = new Observer(*_eventSys._subject);
    }
    virtual ~AGame() = default;

  public:
    parallax::ParallaxSystem &getParallax()
    {
        return this->_parallax;
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
        this->_parallax.update(elapsed);
        this->_eventSys.update(elapsed);
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
        this->_parallax.display();
    }

    /**
     * Method called when the game ends
     */
    virtual void onStop()
    {
    }
};
