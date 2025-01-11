//
// Created by filip on 2025-01-11.
//

#include "Winner.h"

namespace Lemmings {
    void States::Winner::enter()
    {
        this->parent_->initJob(Job::Winner, {0, 0});
    }

    void States::Winner::exit()
    {
    }

    std::unique_ptr<Engine::IState<Lemming>> States::Winner::update(float delta)
    {
        this->frameCounter++;
        if (this->frameCounter >= 7)
            this->parent_->win();
        
        return nullptr;
    }
} // Lemmings