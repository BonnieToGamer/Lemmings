//
// Created by filip on 2024-12-16.
//

#include "Walker.h"

#include "Faller.h"

namespace Lemmings::States {
    void Walker::enter()
    {
        this->parent_->playAnimation("Walker");
        dir = 1;
    }

    void Walker::exit() { }

    std::shared_ptr<Engine::IState<Lemming>> Walker::update(float delta)
    {
        sf::Vector2f pos = this->parent_->getPosition();

        bool falling = true;
        for (int y = 0; y > -4; y--)
        {
            int index = pos.x + (pos.y - y) * this->parent_->map()->width();
            if ((*this->parent_->map())[index].isEnabled())
                falling = false;
        }

        if (falling)
            return std::make_shared<Faller>();
        
        bool nodeEnabled;
        bool walked = false;
        
        
        walked = false;
        for (int x = 0; x < SPEED; x++)
        {
            for (int y = -3; y < 4; y++)
            {
                pos = this->parent_->getPosition();
                pos.x += dir;
                int index = pos.x + (pos.y - y) * this->parent_->map()->width();
                nodeEnabled = (*this->parent_->map())[index].isEnabled();

                if (!nodeEnabled)
                {
                    this->parent_->setPosition(sf::Vector2f(pos.x, pos.y - y));
                    walked = true;
                    break;
                }
            }

            if (walked)
                break;
        }
        
        if (!walked)
            dir *= -1;
        
        return nullptr;
    }
} // Lemmings