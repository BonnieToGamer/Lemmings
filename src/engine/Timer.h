//
// Created by filip on 2024-12-16.
//

#pragma once

namespace Lemmings::Engine {

class Timer {
private:
    float elapsed_;
    float stopTime_;

public:
    Timer(float stopTime);
    bool update(float delta);
};

} // Lemmings
