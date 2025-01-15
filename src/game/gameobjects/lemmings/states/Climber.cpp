//
// Created by filip on 2025-01-15.
//

#include "Climber.h"
#include "Walker.h"

namespace Lemmings::States {

const int CLIMB_OFFSET_X_RIGHT = 3;
const int CLIMB_OFFSET_X_LEFT = -2;
const int CLIMB_OFFSET_Y = -8;
const int FALL_OFFSET_Y = -10;
const int VAULT_OFFSET_Y = -2;
const int VAULT_HEIGHT = -6;
const int FRAME_COUNTER_THRESHOLD = 8;

void Climber::enter()
{
    this->walker_.setParent(this->parent_);
    this->faller_.setParent(this->parent_);
    
    if (this->parent_->getCurrentJob() == Job::Faller)
    {
        this->state_ = Fall;
        this->parent_->initJob(Job::Climber);
    }
    else
    {
        this->state_ = Walk;
        this->parent_->initJob(Job::Climber);
    }
} 

void Climber::exit() { }

void Climber::walkUpdate(float delta)
{
    sf::Vector2i pos = this->parent_->getPosition();
    if (this->parent_->checkCollision(pos.x + (this->parent_->dir() == Right ? CLIMB_OFFSET_X_RIGHT : CLIMB_OFFSET_X_LEFT), pos.y + CLIMB_OFFSET_Y))
    {
        this->state_ = Climb;
        this->parent_->playAnimation(LemmingAnimations::Climb, {0, 0});
        this->frameCounter_ = 0;
        this->parent_->setPosition({pos.x + (this->parent_->dir() == Right ? 1 : 0), pos.y});
        return;
    }
    
    if (const auto newState = this->walker_.update(delta); newState != nullptr)
    {
        this->state_ = Fall;
        this->faller_.enter();
        this->parent_->initJob(Job::Climber);
    }
}

void Climber::fallUpdate(float delta)
{
    if (const auto newState = this->faller_.update(delta); newState != nullptr)
    {
        this->state_ = Walk;
        this->walker_.enter();
        this->parent_->initJob(Job::Climber);
    }
}

void Climber::climbUpdate(float delta)
{
    this->frameCounter_++;
    sf::Vector2i pos = this->parent_->getPosition();

    if (this->parent_->checkCollision(pos.x, pos.y + FALL_OFFSET_Y))
    {
        this->state_ = Fall;
        this->faller_.enter();
        this->parent_->flipSprite();
        this->parent_->setDir(static_cast<HorizontalDirection>(static_cast<int>(this->parent_->dir()) * -1));
        this->parent_->initJob(Job::Climber);
        return;
    }
    
    if (!this->parent_->checkCollision(pos.x + (this->parent_->dir() == Right ? CLIMB_OFFSET_X_RIGHT : CLIMB_OFFSET_X_LEFT), pos.y + CLIMB_OFFSET_Y))
    {
        this->state_ = Vault;
        this->parent_->playAnimation(LemmingAnimations::Vault, {0, 0});
        this->parent_->setPosition({pos.x, pos.y + VAULT_OFFSET_Y});
        return;
    }

    if (frameCounter_ >= FRAME_COUNTER_THRESHOLD)
    {
        this->parent_->setPosition(pos + sf::Vector2i(0, -4));
        this->frameCounter_ = 0;
    }
}

void Climber::vaultUpdate(float delta)
{
    this->frameCounter_++;
    sf::Vector2i pos = this->parent_->getPosition();
    
    if (frameCounter_ >= FRAME_COUNTER_THRESHOLD)
    {
        this->state_ = Walk;
        this->walker_.enter();
        this->parent_->initJob(Job::Climber);
        this->parent_->setPosition({pos.x + 2 * this->parent_->dir(), pos.y + VAULT_HEIGHT});
    }
}

std::unique_ptr<Engine::IState<Lemming>> Climber::update(float delta)
{
    switch (this->state_)
    {
    case Walk:
        this->walkUpdate(delta);
        break;
    case Fall:
        this->fallUpdate(delta);
        break;
    case Climb:
        this->climbUpdate(delta);
        break;
    case Vault:
        this->vaultUpdate(delta);
        break;
    default:
        break;
    }

    return nullptr;
}
}