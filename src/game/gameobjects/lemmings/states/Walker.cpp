//
// Created by filip on 2024-12-16.
//

#include "Walker.h"

#include "Digger.h"
#include "Faller.h"
#include "SFML/Window/Keyboard.hpp"

namespace Lemmings::States {
    void Walker::enter()
    {
        this->parent_->initJob(Job::Walker, {0, 0});
    }

    void Walker::exit() { }

    std::unique_ptr<Engine::IState<Lemming>> Walker::update(float delta)
    {        
        sf::Vector2i pos = this->parent_->getPosition();

        if (this->checkFall(0))
            return std::make_unique<Faller>();

        bool walked = false;
        for (int x = 0; x < SPEED; x++)
        {
            for (int y = -3; y < 4; y++)
            {
                bool nodeEnabled = this->checkWalk(x, y);
                
                if (!nodeEnabled)
                {
                    this->parent_->setPosition(sf::Vector2i(pos.x + this->parent_->dir(), pos.y - y));
                    walked = true;
                    break;
                }
            }

            if (walked)
                break;
        }
        
        if (!walked)
        {
            this->parent_->setDir(static_cast<Direction>(static_cast<int>(this->parent_->dir()) * -1));
            this->parent_->flipSprite();
        }

        this->parent_->checkCollisionExit();
        
        return nullptr;
    }

    bool Walker::checkFall(const float xOffset) const
    {
        sf::Vector2i pos = this->parent_->getPosition();

        bool falling = true;
        for (int y = 0; y > -4; y--)
        {
            if (this->parent_->checkCollision(pos.x + xOffset, pos.y - y))
                falling = false;
        }

        return falling;
    }

    bool Walker::checkWalk(const float xOffset, const float yOffset) const
    {
        sf::Vector2i pos = this->parent_->getPosition();
        bool nodeEnabled = this->parent_->checkCollision(pos.x + this->parent_->dir() + xOffset, pos.y - yOffset);
        
        return nodeEnabled;
    }
} // Lemmings