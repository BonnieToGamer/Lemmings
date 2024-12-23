//
// Created by filip on 2024-12-16.
//

#include "Faller.h"

#include "Walker.h"

namespace Lemmings::States {
    void Faller::enter()
    {
        this->parent_->playAnimation(Lemming::Faller);
    }

    void Faller::exit()
    {
    }

    std::shared_ptr<Engine::IState<Lemming>> Faller::update(float delta)
    {
        sf::Vector2f pos = this->parent_->getPosition();

        if (this->parent_->checkCollision(pos.x, pos.y + 1))
            return std::make_shared<Walker>();

        this->parent_->setPosition(sf::Vector2f(pos.x, pos.y + 1));

        return nullptr;
    }
} // Lemmings