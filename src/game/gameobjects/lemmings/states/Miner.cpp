//
// Created by filip on 2024-12-28.
//

#include "Miner.h"

#include "Faller.h"

namespace Lemmings::States {
    void Miner::digStepOne(const sf::Vector2i& pos, Direction direction)
    {
        sf::Vector2i startPos(
            direction == Left ? pos.x + DIG_STEP_ONE_START_OFFSET_X_LEFT : pos.x + DIG_STEP_ONE_START_OFFSET_X_RIGHT,
            pos.y + DIG_STEP_ONE_START_OFFSET_Y
        );
        
        for (int y = 0; y < DIG_STEP_ONE_HEIGHT; y++) {
            for (int x = 0; x < DIG_STEP_ONE_WIDTH; x++) {
                int xOffset = direction == Left ? DIG_STEP_ONE_WIDTH - 1 - x : x;
                if (shouldSkipFirstStep(y, xOffset)) {
                    continue;
                }
                
                int digX = direction == Left ? startPos.x - xOffset : startPos.x + xOffset;
                this->parent_->tryDig(digX, startPos.y + y);
            }
        }
    }

    bool Miner::shouldSkipFirstStep(int y, int x)
    {
        return (y == 0 && x > 2) || (y == 1 && x > 3);
    }

    bool Miner::digStepTwo(const sf::Vector2i& pos, Direction direction)
    {
        sf::Vector2i startPos(
            direction == Left ? pos.x + DIG_STEP_TWO_START_OFFSET_X_LEFT : pos.x + DIG_STEP_TWO_START_OFFSET_X_RIGHT,
            pos.y + DIG_STEP_TWO_START_OFFSET_Y
        );
        
        for (int y = 0; y < DIG_STEP_TWO_HEIGHT; y++) {
            for (int x = 0; x < DIG_STEP_TWO_WIDTH; x++) {
                int xOffset = direction == Left ? DIG_STEP_TWO_WIDTH - 1 - x : x;
                if (shouldSkipSecondStep(y, xOffset)) {
                    continue;
                }
                int digX = direction == Left ? startPos.x - xOffset : startPos.x + xOffset;
                this->parent_->tryDig(digX, startPos.y + y);
            }
        }
        return !this->parent_->checkCollision(pos.x, pos.y + 2);
    }

    bool Miner::shouldSkipSecondStep(int y, int x)
    {
        return (y == 0 && x == 10) || 
            (y == 1 && x == 10) ||
            (y == 9 && x == 0) ||
            (y == 10 && (x <= 2 || x == 10)) || 
            (y == 11 && (x <= 4 || x >= 9));
    }

    void Miner::resetMineCounter(const sf::Vector2i& pos)
    {
        sf::Vector2i offset = this->parent_->dir() == Left ? 
            sf::Vector2i(MINE_COUNTER_RESET_OFFSET_X_LEFT, MINE_COUNTER_RESET_OFFSET_Y) : 
            sf::Vector2i(MINE_COUNTER_RESET_OFFSET_X_RIGHT, MINE_COUNTER_RESET_OFFSET_Y);
        
        this->parent_->setPosition(pos + offset);
        this->mineCounter = 0;
    }

    void Miner::enter()
    {
        this->parent_->playAnimation(Job::Miner);
        this->parent_->updateCurrentJob(Job::Miner);
        this->parent_->setAnimationOffset(this->parent_->dir() == Left ? 
            sf::Vector2i(ANIMATION_OFFSET_X_LEFT, ANIMATION_OFFSET_Y) : 
            sf::Vector2i(ANIMATION_OFFSET_X_RIGHT, ANIMATION_OFFSET_Y));
    }

    void Miner::exit()
    {
    }

    std::shared_ptr<Engine::IState<Lemming>> Miner::update(float delta)
    {
        this->mineCounter++;
        sf::Vector2i pos = this->parent_->getPosition();

        if (this->mineCounter == MINE_COUNTER_STEP_ONE) {
            digStepOne(pos, this->parent_->dir());
        } 
        else if (this->mineCounter == MINE_COUNTER_STEP_TWO) {
            if (digStepTwo(pos, this->parent_->dir())) {
                return std::make_shared<Faller>();
            }
        } 
        else if (this->mineCounter == MINE_COUNTER_RESET_THRESHOLD) {
            resetMineCounter(pos);
        }

        return nullptr;
    }
} // Lemmings