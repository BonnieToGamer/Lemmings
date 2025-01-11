//
// Created by filip on 2024-12-16.
//

#include "Lemming.h"

#include "../Exit.h"
#include "../../../engine/Core.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "states/Blocker.h"
#include "states/Digger.h"
#include "states/Faller.h"
#include "states/Miner.h"
#include "states/Walker.h"
#include "states/Winner.h"

namespace Lemmings {
    Engine::Event<Lemming*> Lemming::deathEvent;
    Engine::Event<Lemming*> Lemming::winEvent;

    void Lemming::addAnimation(Job job, uint amountOfFrames, const sf::Vector2u& offset, const bool addDirt)
    {
        auto animation = std::make_unique<Engine::SpriteSheetAnimation>(
            this->lemmingSpriteSheet.get(),
            Engine::SpriteSheetAnimation::Right,
            amountOfFrames,
            sf::Vector2u(offset.x, offset.y)
        );
        
        this->animations_.addAnimation(job, std::move(animation));
        
        if (!addDirt)
            return;

        animation = std::make_unique<Engine::SpriteSheetAnimation>(
            this->dirtSpriteSheet.get(),
            Engine::SpriteSheetAnimation::Right,
            amountOfFrames,
            sf::Vector2u(offset.x,offset.y)
        );
        
        this->dirtAnimations_.addAnimation(job, std::move(animation));
    }

    void Lemming::die()
    {
        this->deathEvent.invoke(this);
    }

    Lemming::Lemming(Map* map, LevelData* data) : map_(map), data_(data) { }

    void Lemming::init()
    {
        this->lemmingTexture_ = Engine::Core::contentManager->getTexture("lemming");
        this->dirtTexture_ = Engine::Core::contentManager->getTexture("dirt");

        this->lemmingSpriteSheet = std::make_unique<Engine::SpriteSheet>(sf::Vector2u(TEXTURE_WIDTH, TEXTURE_HEIGHT), lemmingTexture_);
        this->dirtSpriteSheet = std::make_unique<Engine::SpriteSheet>(sf::Vector2u(TEXTURE_WIDTH, TEXTURE_HEIGHT), dirtTexture_);

        this->lemmingSpriteSheet->init();
        this->dirtSpriteSheet->init();

        this->addAnimation(Walker, 8, {0, 0}, false);
        this->addAnimation(Faller, 4, {0, 1}, false);
        this->addAnimation(Digger, 15, {0, 2}, true);
        this->addAnimation(Miner, 25, {0, 3}, true);
        this->addAnimation(Winner, 8, {0, 4}, false);
        this->addAnimation(Blocker, 16, {0, 5}, false);

        this->stateMachineManager_ =
            std::make_unique<Engine::StateMachineManager<Lemming>>(std::make_unique<States::Faller>(), this);
    }

    void Lemming::update(float delta)
    {
        this->stateMachineManager_->update(delta);
        this->animations_.getCurrentAnimation()->nextFrame();
        if (this->dirtAnimations_.getCurrentAnimation() != nullptr) this->dirtAnimations_.getCurrentAnimation()->nextFrame();
    }

    void Lemming::draw(sf::RenderTarget& renderTarget)
    {
        this->lemmingSpriteSheet->draw(renderTarget);

        if (this->dirtAnimations_.getCurrentAnimation() == nullptr)
            this->dirtSpriteSheet->draw(renderTarget);
        
        sf::RectangleShape rectShape(sf::Vector2f(1.0f, 1.0f));
        rectShape.setFillColor(sf::Color::Green);
        rectShape.setPosition(this->position_.x, this->position_.y);
        renderTarget.draw(rectShape);
    }

    sf::Vector2i Lemming::getPosition() const
    {
        return this->position_;
    }

    void Lemming::setPosition(const sf::Vector2i& newPos)
    {
        if (newPos.y < 0 || newPos.y >= this->map_->height() || newPos.x < 0 || newPos.x >= this->map_->width())
            this->die();
        
        this->position_ = newPos;

        const sf::Vector2i actualPos = this->getActualPos();
        this->lemmingSpriteSheet->setPosition(actualPos.x, actualPos.y);
        this->dirtSpriteSheet->setPosition(actualPos.x, actualPos.y);
    }

    Map* Lemming::map()
    {
        return this->map_;
    }

    void Lemming::initJob(Job job, sf::Vector2i offset)
    {
        this->currentJob_ = job;
        
        this->animations_.changeAnimation(job);
        this->animations_.getCurrentAnimation()->resetAnimation();

        this->dirtAnimations_.changeAnimation(job);
        if (this->dirtAnimations_.getCurrentAnimation() != nullptr)
            this->dirtAnimations_.getCurrentAnimation()->resetAnimation();

        this->lemmingSpriteSheet->setOffset(offset);
        this->dirtSpriteSheet->setOffset(offset);
    }

    void Lemming::flipSprite()
    {
        this->lemmingSpriteSheet->flipSprite();
        this->dirtSpriteSheet->flipSprite();
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
        case Blocker:
            state = std::make_unique<States::Blocker>();
            break;
        default:
            state = nullptr;
            break;
        }

        if (state == nullptr)
            return false;
        
        this->stateMachineManager_->changeState(std::move(state));
        return true;
    }

    void Lemming::checkCollisionExit()
    {
        sf::Vector2i actualPos = this->position_;
        sf::IntRect rect(actualPos.x, actualPos.y, 1, 1);
        if (Exit::collisionArea.intersects(rect))
            this->stateMachineManager_->changeState(std::make_unique<States::Winner>());
    }

    void Lemming::win()
    {
        this->winEvent.invoke(this);
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

    void Lemming::placeCell(int x, int y, sf::Color color) const
    {
        if (x < 0 || x >= this->map_->width() ||
            y < 0 || y >= this->map_->height())
        return;
        
        const int index = x + y * this->map_->width();
        this->map_->changeNode(index, true, color);
    }
} // Lemmings