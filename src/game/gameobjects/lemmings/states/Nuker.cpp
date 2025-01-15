//
// Created by filip on 2025-01-15.
//

#include "Nuker.h"

namespace Lemmings {
    States::Nuker::Nuker(Job previousJob) : prevJob_(previousJob)
    {
        
    }

    void States::Nuker::explode()
    {
        this->parent_->playAnimation(Explosion, {-2, 0});
        this->exploded = true;
    }

    void States::Nuker::enter()
    {
        if (this->prevJob_ == Faller || this->prevJob_ == Floater)
        {
            this->explode();
            return;
        }

        this->parent_->playAnimation(Nuke, {0, 0});
    }

    void States::Nuker::exit()
    {
    }

    std::unique_ptr<Engine::IState<Lemming>> States::Nuker::update(float delta)
    {
        if (this->exploded && this->animationIndex_ % 3 == 0 && this->animationIndex_ != 0)
            this->parent_->die();
        
        if (this->animationIndex_ % 15 == 0 && this->animationIndex_ != 0)
        {
            this->explode();
            this->animationIndex_ = 0;
        }
        
        this->animationIndex_++;
        return nullptr;
    }
} // Lemmings