//
// Created by filip on 2024-12-16.
//

#include "Lemming.h"

#include <complex.h>
#include <stdexcept>

#include "SFML/Graphics/RectangleShape.hpp"
#include "states/Digger.h"
#include "states/Miner.h"
#include "states/Walker.h"

namespace Lemmings {
    std::shared_ptr<sf::Texture> Lemming::lemmingTexture_;
    std::shared_ptr<sf::Texture> Lemming::lemmingMiningTexture_;

    void Lemming::addAnimation(Job job, uint amountOfFrames, uint row, const sf::Vector2u& spriteSize, const sf::Vector2i& offset, std::shared_ptr<sf::Texture> texture)
    {
        auto animation = std::make_shared<Engine::AnimatedTexture>(texture, spriteSize, true);
        animation->addSpriteSheetAnim(amountOfFrames, row, offset, 0);
        this->animations_.emplace(job, animation);
    }

    void Lemming::die()
    {
        this->deathEvent.invoke(this);
    }

    Lemming::Lemming(Map* map) : map_(map) { }

    void Lemming::init()
    {
        this->stateMachineManager_ =
            std::make_unique<Engine::StateMachineManager<Lemming>>(std::make_unique<States::Walker>(), this);

        if (lemmingTexture_ == nullptr)
        {
            lemmingTexture_ = std::make_shared<sf::Texture>();
        
            if (!lemmingTexture_->loadFromFile(ASSETS_PATH"lemming.png"))
                throw std::runtime_error("Couldn't load texture!");
        }

        if (lemmingMiningTexture_ == nullptr)
        {
            lemmingMiningTexture_ = std::make_shared<sf::Texture>();
        
            if (!lemmingMiningTexture_->loadFromFile(ASSETS_PATH"lemming_miner.png"))
                throw std::runtime_error("Couldn't load texture!");
        }

        sf::Vector2u spriteSize(TEXTURE_WIDTH, TEXTURE_HEIGHT);
        sf::Vector2u mineSpriteSize(TEXTURE_WIDTH + 1, TEXTURE_HEIGHT);
        
        addAnimation(Job::Walker, 8, 0, spriteSize, {0, 0}, lemmingTexture_);
        addAnimation(Job::Faller, 4, 1, spriteSize, {0, 1}, lemmingTexture_);
        addAnimation(Job::Digger, 15, 2, spriteSize, {0, 2}, lemmingTexture_);
        addAnimation(Job::Miner, 25, 0, mineSpriteSize, {2, 4}, lemmingMiningTexture_);
        
        this->currentAnimatedTexture_ = this->animations_[Job::Walker];
    }

    void Lemming::update(float delta)
    {
        this->stateMachineManager_->update(delta);
        this->currentAnimatedTexture_->nextFrame();
    }

    void Lemming::draw(sf::RenderTarget& renderTarget)
    {
        sf::Vector2i actualPos = this->getActualPos();
        this->currentAnimatedTexture_->setPosition(actualPos.x, actualPos.y);
        this->currentAnimatedTexture_->draw(renderTarget);
        
        sf::RectangleShape rectShape(sf::Vector2f(1.0f, 1.0f));
        rectShape.setFillColor(sf::Color::Green);
        rectShape.setPosition(this->position_.x, this->position_.y);
        renderTarget.draw(rectShape);
    }

    const sf::Vector2i& Lemming::getPosition()
    {
        return this->position_;
    }

    void Lemming::setPosition(const sf::Vector2i& newPos)
    {
        if (newPos.y < 0 || newPos.y >= this->map_->height() || newPos.x < 0 || newPos.x >= this->map_->width())
            this->die();
        
        this->position_ = newPos;
        if (this->currentAnimatedTexture_ == nullptr)
            return;

        const sf::Vector2i actualPos = this->getActualPos();
        this->currentAnimatedTexture_->setPosition(actualPos.x, actualPos.y);
    }

    Map* Lemming::map()
    {
        return this->map_;
    }

    void Lemming::playAnimation(Job job)
    {
        if (const auto itr = this->animations_.find(job); itr == this->animations_.end())
            return;
            
        this->currentAnimatedTexture_ = this->animations_[job];
        this->currentAnimatedTexture_->init();
        this->currentAnimatedTexture_->setFlipped(this->currentDir_);
    }

    void Lemming::setAnimationOffset(sf::Vector2i offset)
    {
        this->currentAnimatedTexture_->setOffset(offset);
    }

    void Lemming::flipSprite() const
    {
        this->currentAnimatedTexture_->flipSprite();
    }

    Direction Lemming::dir() const
    {
        return this->currentDir_;
    }

    void Lemming::setDir(const Direction newDir)
    {
        this->currentDir_ = newDir;
    }

    sf::Vector2i Lemming::getActualPos()
    {
        return {
            static_cast<int>(this->position_.x - TEXTURE_WIDTH / 2 + (this->currentDir_ == 1 ? 1 : 0)),
            static_cast<int>(this->position_.y - TEXTURE_HEIGHT + 1)};
    }

    sf::Vector2i Lemming::getSize()
    {
        return {static_cast<int>(TEXTURE_WIDTH), static_cast<int>(TEXTURE_HEIGHT)};
    }
    
    void Lemming::updateCurrentJob(Job job)
    {
        this->currentJob_ = job;
    }

    Job Lemming::getCurrentJob() const
    {
        return this->currentJob_;
    }

    bool Lemming::tryAssignJob(const Job job) const
    {
        if (this->currentJob_ != Job::Walker)
            return false;
        
        std::unique_ptr<Engine::IState<Lemming>> state;

        switch (job)
        {
        case Digger:
            state = std::make_unique<States::Digger>();
            break;
        case Miner:
            state = std::make_unique<States::Miner>();
            break;
        default:
            state = nullptr;
            break;
        }

        if (state != nullptr)
        {
            this->stateMachineManager_->changeState(std::move(state));
            return true;
        }
        
        return false;
    }

    bool Lemming::checkCollision(const int x, const int y) const
    {
        if (x < 0 || x >= this->map_->width() ||
            y < 0 || y >= this->map_->height())
            return false;

        const int index = x + y * this->map_->width();
        return (*this->map_)[index].isEnabled();
    }

    void Lemming::tryDig(int x, int y) const
    {
        if (x < 0 || x >= this->map_->width() ||
            y < 0 || y >= this->map_->height())
            return;
        
        const int index = x + y * this->map_->width();
        this->map_->changeNode(index, false);
    }

    void Lemming::destroyTextures()
    {
        lemmingTexture_ = nullptr;
        lemmingMiningTexture_ = nullptr;
    }
} // Lemmings