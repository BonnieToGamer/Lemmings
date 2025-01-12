//
// Created by filip on 2025-01-11.
//

#include "Builder.h"

#include "Walker.h"

namespace Lemmings::States {
    void Builder::enter()
    {
        this->parent_->initJob(Job::Builder, {0, 0});
    }

    void Builder::exit()
    {
    }

    std::unique_ptr<Engine::IState<Lemming>> Builder::update(float delta)
    {
        this->frameCounter++;

        if (shrugState)
        {
            if (this->frameCounter == 7)
                return std::make_unique<Walker>();
            
            return nullptr;
        }

        if (this->frameCounter == 9)
        {
            sf::Vector2i pos = this->parent_->getPosition();
            this->parent_->placeCell(pos.x - 1, pos.y, sf::Color(BUILD_BLOCK_COLOR), this->parent_->dir());
            this->parent_->placeCell(pos.x + 0, pos.y, sf::Color(BUILD_BLOCK_COLOR), this->parent_->dir());
            this->parent_->placeCell(pos.x + 1, pos.y, sf::Color(BUILD_BLOCK_COLOR), this->parent_->dir());
            this->parent_->placeCell(pos.x + 2, pos.y, sf::Color(BUILD_BLOCK_COLOR), this->parent_->dir());
            this->parent_->placeCell(pos.x + 3, pos.y, sf::Color(BUILD_BLOCK_COLOR), this->parent_->dir());
            this->parent_->placeCell(pos.x + 4, pos.y, sf::Color(BUILD_BLOCK_COLOR), this->parent_->dir());
        }
        
        if (this->frameCounter >= 16)
        {
            sf::Vector2i pos = this->parent_->getPosition();
            this->parent_->setPosition({pos.x + 2, pos.y - 1});
            this->frameCounter = 0;
            this->placedTiles++;
        }

        if (this->placedTiles >= AMOUNT_OF_TILES)
        {
            this->frameCounter = 0;
            this->parent_->playShrugAnimation();
            this->shrugState = true;
        }
        
        return nullptr;
    }
} // Lemmings