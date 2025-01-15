//
// Created by filip on 2024-12-16.
//

#pragma once

#include "Event.h"

namespace Lemmings::Engine {

class Timer {
private:
    float elapsed_;
    float stopTime_;

public:
    Event<> onTimerCompleteEvent;
    
    explicit Timer(float stopTime);
    bool update(float delta);
    void changeStopTime(float newTime);
    float getElapsed() const;
};

} // Lemmings
