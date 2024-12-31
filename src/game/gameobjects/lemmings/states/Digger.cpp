//
// Created by filip on 2024-12-24.
//

#include "Digger.h"

#include "Faller.h"

namespace Lemmings::States {
    void Digger::enter()
    {
        this->parent_->playAnimation(Job::Digger);
        this->parent_->updateCurrentJob(Job::Digger);
    }

    void Digger::exit()
    {
    }

    std::shared_ptr<Engine::IState<Lemming>> Digger::digDown()
    {
        sf::Vector2i pos = this->parent_->getPosition();
        int digStartY = -1;
        int digStopY = 2;
        int digStartX = this->parent_->dir() == Right ? -3 : -5;
        int digStopX = this->parent_->dir() == Right ? 6 : 4;
        
        for (int yOffset = digStartY; yOffset < digStopY; yOffset++)
        {
            for (int xOffset = digStartX; xOffset < digStopX; xOffset++)
            {
                this->parent_->tryDig(pos.x + xOffset, pos.y + yOffset);
            }
        }

        this->parent_->setPosition({pos.x, pos.y + 1});

        bool allGone = true;
        for (int i = digStartX; i < digStopX; i++)
        {
            if (this->parent_->checkCollision(pos.x + i, pos.y + 2))
                allGone = false;
        }

        if (allGone)
            return std::make_shared<Faller>();

        return nullptr;
    }

    std::shared_ptr<Engine::IState<Lemming>> Digger::update(float delta)
    {
        this->digCounter_++;

        int remainder = this->digCounter_ % 8;
        if (remainder == 0)
            return this->digDown();
        
        return nullptr;
    }
} // Lemmings