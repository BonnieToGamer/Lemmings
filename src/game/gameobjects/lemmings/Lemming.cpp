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
    std::shared_ptr<sf::Texture> Lemming::dirtTexture_;
    Engine::Event<Lemming*> Lemming::deathEvent;

    void Lemming::addAnimation(Job job, uint amountOfFrames, uint row, const sf::Vector2u& spriteSize, const sf::Vector2i& offset, std::shared_ptr<sf::Texture> texture, bool addDirt, std::shared_ptr<sf::Texture> dirtTexture)
    {
        auto animation = std::make_shared<Engine::AnimatedTexture>(texture, spriteSize, true);
        animation->addSpriteSheetAnim(amountOfFrames, row, offset, 0);
        this->animations_.emplace(job, animation);

        if (!addDirt && !dirtTexture)
            return;

        animation = std::make_shared<Engine::AnimatedTexture>(dirtTexture, spriteSize, true);
        animation->addSpriteSheetAnim(amountOfFrames, row, offset, 0);
        // animation->setColor()
        this->dirtAnimations_.emplace(job, animation);
    }

    void Lemming::die()
    {
        this->deathEvent.invoke(this);
    }

    Lemming::Lemming(Map* map) : map_(map) { }

    void Lemming::loadTexture(std::shared_ptr<sf::Texture>& texture, const std::string& textureName)
    {
        if (texture == nullptr)
        {
            texture = std::make_shared<sf::Texture>();
        
            if (!texture->loadFromFile(ASSETS_PATH + textureName))
                throw std::runtime_error("Couldn't load texture!");
        }
    }

    void Lemming::init()
    {
        this->stateMachineManager_ =
            std::make_unique<Engine::StateMachineManager<Lemming>>(std::make_unique<States::Walker>(), this);

        this->loadTexture(lemmingTexture_, "lemming.png");
        this->loadTexture(dirtTexture_, "dirt.png");

        sf::Vector2u spriteSize(TEXTURE_WIDTH, TEXTURE_HEIGHT);
        sf::Vector2u mineSpriteSize(TEXTURE_WIDTH + 1, TEXTURE_HEIGHT);
        
        this->addAnimation(Job::Walker, 8, 0, spriteSize, {0, 0}, lemmingTexture_);
        this->addAnimation(Job::Faller, 4, 1, spriteSize, {0, 1}, lemmingTexture_);
        this->addAnimation(Job::Digger, 15, 2, spriteSize, {0, 2}, lemmingTexture_, true, dirtTexture_);
        this->addAnimation(Job::Miner, 25, 3, mineSpriteSize, {2, 4}, lemmingTexture_);

        this->playAnimation(Walker);
        // this->currentAnimtedTexture_ = this->animations_[Job::Walker];
    }

    void Lemming::update(float delta)
    {
        this->stateMachineManager_->update(delta);
        this->currentAnimatedTexture_->nextFrame();
        if (this->currentAnimatedDirtTexture_ != nullptr) this->currentAnimatedDirtTexture_->nextFrame();
    }

    void Lemming::draw(sf::RenderTarget& renderTarget)
    {
        this->currentAnimatedTexture_->draw(renderTarget);

        if (this->currentAnimatedDirtTexture_ != nullptr)
            this->currentAnimatedDirtTexture_->draw(renderTarget);
        
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

        if (this->currentAnimatedDirtTexture_ != nullptr)
            this->currentAnimatedDirtTexture_->setPosition(actualPos.x, actualPos.y);
    }

    Map* Lemming::map()
    {
        return this->map_;
    }

    void Lemming::playAnimation(Job job)
    {
        if (const auto itr = this->animations_.find(job); itr == this->animations_.end())
            return;

        sf::Vector2i currentPos = this->getActualPos();
        this->currentAnimatedTexture_ = this->animations_[job];
        this->currentAnimatedTexture_->init();
        this->currentAnimatedTexture_->setFlipped(this->currentDir_);
        this->currentAnimatedTexture_->setPosition(currentPos.x, currentPos.y);

        if (const auto itr = this->dirtAnimations_.find(job); itr == this->dirtAnimations_.end())
        {
            this->currentAnimatedDirtTexture_ = nullptr;
            return;
        }

        this->currentAnimatedDirtTexture_ = this->dirtAnimations_[job];
        this->currentAnimatedDirtTexture_->init();
        this->currentAnimatedDirtTexture_->setFlipped(this->currentDir_);
        this->currentAnimatedDirtTexture_->setPosition(currentPos.x, currentPos.y);
    }

    void Lemming::setAnimationOffset(sf::Vector2i offset)
    {
        this->currentAnimatedTexture_->setOffset(offset);
    }

    void Lemming::flipSprite()
    {
        this->currentAnimatedTexture_->flipSprite();
        this->setPosition(this->position_);
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
    
    void Lemming::forceUpdateNewJob(Job job)
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
        dirtTexture_ = nullptr;
    }
} // Lemmings