//
// Created by filip on 2025-01-12.
//

#include "Floater.h"

#include "Faller.h"

namespace Lemmings::States
{
    // this class could do with less magic numbers and a StateMachineManager,
    // but I didn't have the time to implement it.

    
    void Floater::enter()
    {
        this->walker_.setParent(this->parent_);
        this->faller_.setParent(this->parent_);
        
        if (this->parent_->getCurrentJob() == Job::Floater)
        {
            this->state_ = Fall;
            this->parent_->initJob(Job::Floater);
        }
        
        else
        {
            this->state_ = Walk;
            this->parent_->initJob(Job::Floater);
        }
    } 

    void Floater::exit() { }

    void Floater::walkUpdate(float delta)
    {
        if (const auto newState = this->walker_.update(delta); newState != nullptr)
        {
            this->state_ = Fall;
            this->faller_.enter();
            this->parent_->initJob(Job::Floater);
        }
    }

    void Floater::fallUpdate(float delta)
    {
        if (const auto newState = this->faller_.update(delta); newState != nullptr)
        {
            this->state_ = Walk;
            this->walker_.enter();
            this->parent_->initJob(Job::Floater);
            return;
        }

        if (fallFrames_ >= MAX_FALL_FRAMES_UNTIL_PARACHUTE)
        {
            this->state_ = ParachuteOpen;
            this->parent_->playAnimation(LemmingAnimations::ParachuteOpen, {0, 0});
            this->frameCounter_ = 0;
        }

        fallFrames_++;
    }

    void Floater::parachuteOpenUpdate(float delta)
    {
        this->frameCounter_++;
        if (this->frameCounter_ == 4)
        {
            this->state_ = ParachuteGlide;
            this->parent_->playAnimation(ParachuteHang, {0, 0});
            this->frameCounter_ = 0;
            return;
        }

        this->fallAndCollide();
    }

    void Floater::parachuteGlideUpdate(float delta)
    {
        this->fallAndCollide();
    }

    void Floater::fallAndCollide()
    {
        sf::Vector2i pos = this->parent_->getPosition();

        if (this->parent_->checkCollision(pos.x, pos.y + 1))
        {
            this->state_ = Walk;
            this->walker_.enter();
            this->parent_->initJob(Job::Floater);
            
            return;
        }

        this->parent_->setPosition({pos.x, pos.y + 1});
    }
    
    std::unique_ptr<Engine::IState<Lemming>> Floater::update(float delta)
    {
        switch (this->state_)
        {
        case Walk:
            this->walkUpdate(delta);
            break;
        case Fall:
            this->fallUpdate(delta);
            break;
        case ParachuteOpen:
            this->parachuteOpenUpdate(delta);
            break;
        case ParachuteGlide:
            this->parachuteGlideUpdate(delta);
            break;
        default:
            break;
        }

        return nullptr;
    }
}
