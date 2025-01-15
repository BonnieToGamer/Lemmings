//
// Created by filip on 2024-12-16.
//

#include "Timer.h"

namespace Lemmings {
    Engine::Timer::Timer(float stopTime) : stopTime_(stopTime), elapsed_(0) { }

    bool Engine::Timer::update(float delta)
    {
        this->elapsed_ += delta;

        if (this->elapsed_ >= this->stopTime_)
        {
            this->elapsed_ = 0;
            this->onTimerCompleteEvent.invoke();
            return true;    
        }

        return false;
    }

    void Engine::Timer::changeStopTime(float newTime)
    {
        this->stopTime_ = newTime;
    }

    float Engine::Timer::getElapsed() const
    {
        return this->elapsed_;
    }
} // Lemmings