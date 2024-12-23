//
// Created by filip on 2024-12-24.
//

#include "Digger.h"

#include "Faller.h"

namespace Lemmings::States {
    void Digger::enter()
    {
        this->parent_->playAnimation(Lemming::Digger);
    }

    void Digger::exit()
    {
    }

    std::shared_ptr<Engine::IState<Lemming>> Digger::digDown()
    {
        sf::Vector2f pos = this->parent_->getPosition();
        for (int yOffset = -4; yOffset < 2; yOffset++)
        {
            for (int xOffset = -3; xOffset < 6; xOffset++)
            {
                int index = pos.x + xOffset + (pos.y + yOffset) * this->parent_->map()->width();
                (*this->parent_->map())[index].disable();
            }
        }

        this->parent_->setPosition({pos.x, pos.y + 1});

        bool allGone = true;
        for (int i = -3; i < 6; i++)
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
        if (remainder == 0 || remainder == 1)
            return this->digDown();
        
        return nullptr;
    }
} // Lemmings