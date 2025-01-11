//
// Created by filip on 2025-01-11.
//

#include "Blocker.h"

namespace Lemmings::States {
    void Blocker::enter()
    {
        this->parent_->initJob(Job::Blocker, {0, 0});
        sf::Vector2i pos = this->parent_->getPosition();

        for (int i = -4; i < 10; i++)
        {
            this->parent_->placeCell(pos.x - 3, pos.y - i, sf::Color::Transparent);
            this->parent_->placeCell(pos.x + 6, pos.y - i, sf::Color::Transparent);
        }
    }

    void Blocker::exit()
    {
    }

    std::unique_ptr<Engine::IState<Lemming>> Blocker::update(float delta)
    {
        return nullptr;
    }
} // Lemmings