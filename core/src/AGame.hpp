#pragma once

#include <./EventSystem.hpp>
#include <chrono>

class AGame {
  private:
    bool isRunning{false};
    double framerateLimit_{60};
    Game::EventSystem _eventSys;

  protected:
    AGame()
    {
    }
    virtual ~AGame() = default;

  public:
    /**
     * Paces the game loop to match [getFrequency] updates per second
     *
     * This method is called in the main loop, and must wait until the next tick
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
        return this->framerateLimit_;
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
     * Start the game
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
     * Stop the game execution
     *
     * The game will fully stop on next tick
     */
    void stop()
    {
        this->isRunning = false;
        this->onStop();
    }

    /**
     * Set game update rate
     *
     * @param limit maximum number of updates per second
     */
    void setFramerateLimit(double limit)
    {
        this->framerateLimit_ = limit;
    }

  private:
    /**
     * Updates the game
     */
    void update(long elapsed)
    {
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
    }
    /**
     * Method called when the game ends
     */
    virtual void onStop()
    {
    }
};
