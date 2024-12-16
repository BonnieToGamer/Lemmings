//
// Created by filip on 2024-12-16.
//

#include "Faller.h"

#include "Walker.h"

namespace Lemmings::States {
    void Faller::enter()
    {
        this->parent_->playAnimation("Faller");
    }

    void Faller::exit()
    {
    }

    std::shared_ptr<Engine::IState<Lemming>> Faller::update(float delta)
    {
        sf::Vector2f pos = this->parent_->getPosition();

        int index = pos.x + (pos.y + 1) * this->parent_->map()->width();
        if ((*this->parent_->map())[index].isEnabled())
            return std::make_shared<Walker>();

        this->parent_->setPosition(sf::Vector2f(pos.x, pos.y + 1));

        return nullptr;
    }
} // Lemmings