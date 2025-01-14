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
        this->parent_->initJob(Job::Walker);
        this->parent_->playAnimation(LemmingAnimations::Walk, {0, 0});
    }

    void Walker::exit() { }

    std::unique_ptr<Engine::IState<Lemming>> Walker::update(float delta)
    {
        const sf::Vector2i pos = this->parent_->getPosition();

        if (this->checkFall(this->parent_->dir()))
            return std::make_unique<Faller>();

        bool walked = false;

        for (int y = 0; y > -4; y--)
        {
            if (bool nodeEnabled = this->checkWalk(0, y); !nodeEnabled)
            {
                this->parent_->setPosition(sf::Vector2i(pos.x + this->parent_->dir(), pos.y - y));
                walked = true;
                continue;
            }
            
            break;
        }

        if (!walked)
        {
            for (int y = 0; y < 4; y++)
            {            
                bool nodeEnabled = this->checkWalk(0, y);
            
                if (!nodeEnabled)
                {
                    this->parent_->setPosition(sf::Vector2i(pos.x + this->parent_->dir(), pos.y - y));
                    walked = true;
                    break;
                }
            }
        }
        
        if (!walked)
        {
            this->parent_->setDir(static_cast<HorizontalDirection>(static_cast<int>(this->parent_->dir()) * -1));
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
            {
                falling = false;
                break;
            }
        }

        if (falling)
            this->parent_->setPosition({static_cast<int>(pos.x + xOffset), pos.y});

        return falling;
    }

    bool Walker::checkWalk(const float xOffset, const float yOffset) const
    {
        const sf::Vector2i pos = this->parent_->getPosition();
        const bool nodeEnabled = this->parent_->checkCollision(pos.x + this->parent_->dir() + xOffset, pos.y - yOffset, this->parent_->dir());
        
        return nodeEnabled;
    }
} // Lemmings