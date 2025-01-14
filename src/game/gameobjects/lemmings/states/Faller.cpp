//
// Created by filip on 2024-12-16.
//

#include "Faller.h"

#include "Walker.h"

namespace Lemmings::States {
    void Faller::enter()
    {
        this->parent_->initJob(Job::Faller);
        this->parent_->playAnimation(Fall, {0, 0});
    }

    void Faller::exit()
    {
    }

    std::unique_ptr<Engine::IState<Lemming>> Faller::update(float delta)
    {
        const sf::Vector2i pos = this->parent_->getPosition();

        for (int i = 1; i <= 4; i++)
        {
            if (this->parent_->checkCollision(pos.x, pos.y + i))
                return std::make_unique<Walker>();

            this->parent_->setPosition(sf::Vector2i(pos.x, pos.y + i));
        }
        
        return nullptr;
    }
} // Lemmings