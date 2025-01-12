//
// Created by filip on 2025-01-11.
//

#include "Blocker.h"

namespace Lemmings::States {
    void Blocker::enter()
    {
        this->parent_->initJob(Job::Blocker);
        this->parent_->playAnimation(Block, {0, 0});
        sf::Vector2i pos = this->parent_->getPosition();

        for (int i = -4; i < 10; i++)
        {
            if (!this->parent_->checkCollision(pos.x - 3, pos.y - i))
            {
                this->parent_->placeCell(pos.x - 3, pos.y - i, sf::Color::Red);
                this->placed_.emplace_back(pos.x - 3, pos.y - i);
            }
            
            if (!this->parent_->checkCollision(pos.x + 6, pos.y - i))
            {
                this->parent_->placeCell(pos.x + 6, pos.y - i, sf::Color::Red);
                this->placed_.emplace_back(pos.x + 6, pos.y - i);
            }
        }
    }

    void Blocker::exit()
    {
        for (const auto pos : this->placed_)
            this->parent_->tryDig(pos.x, pos.y);
    }

    std::unique_ptr<Engine::IState<Lemming>> Blocker::update(float delta)
    {
        return nullptr;
    }
} // Lemmings