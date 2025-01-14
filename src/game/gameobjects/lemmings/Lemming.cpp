//
// Created by filip on 2024-12-16.
//

#include "Lemming.h"

#include <iostream>

#include "../Exit.h"
#include "../../../engine/Core.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "states/Blocker.h"
#include "states/Builder.h"
#include "states/Digger.h"
#include "states/Faller.h"
#include "states/Floater.h"
#include "states/Miner.h"
#include "states/Walker.h"
#include "states/Winner.h"

namespace Lemmings {
    Engine::Event<Lemming*> Lemming::deathEvent;
    Engine::Event<Lemming*> Lemming::winEvent;

    void Lemming::addAnimation(LemmingAnimations jobAnimation, uint amountOfFrames, const sf::Vector2u& offset)
    {
        auto animation = std::make_unique<Engine::SpriteSheetAnimation>(
            this->lemmingSpriteSheet.get(),
            Engine::SpriteSheetAnimation::Right,
            amountOfFrames,
            sf::Vector2u(offset.x, offset.y)
        );
        
        this->animations_.addAnimation(jobAnimation, std::move(animation));

        animation = std::make_unique<Engine::SpriteSheetAnimation>(
            this->dirtSpriteSheet.get(),
            Engine::SpriteSheetAnimation::Right,
            amountOfFrames,
            sf::Vector2u(offset.x,offset.y)
        );
        
        this->dirtAnimations_.addAnimation(jobAnimation, std::move(animation));
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
        this->dirtSpriteSheet->setColor(this->data_->indexToColor.at(static_cast<LevelData::DirtIndexColor>(this->data_->dirtIndex)));

        this->lemmingSpriteSheet->init();
        this->dirtSpriteSheet->init();

        this->addAnimation(Walk, 8, {0, 0});
        this->addAnimation(Fall, 4, {0, 1});
        this->addAnimation(Dig, 15, {0, 2});
        this->addAnimation(Mine, 24, {0, 3});
        this->addAnimation(Win, 8, {0, 4});
        this->addAnimation(Block, 16, {0, 5});
        this->addAnimation(Build, 16, {0, 6});
        this->addAnimation(Shrug, 7, {0, 7});
        this->addAnimation(ParachuteOpen, 4, {0, 8});
        this->addAnimation(ParachuteHang, 6, {0, 9});

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

    Map* Lemming::map() const
    {
        return this->map_;
    }

    void Lemming::initJob(Job job)
    {
        this->currentJob_ = job;
    }

    void Lemming::playAnimation(LemmingAnimations animation, sf::Vector2i offset)
    {
        this->animations_.changeAnimation(animation);
        this->animations_.getCurrentAnimation()->resetAnimation();
        this->lemmingSpriteSheet->setOffset(offset);
        this->lemmingSpriteSheet->setFlipped(this->currentDir_);

        this->dirtAnimations_.changeAnimation(animation);
        this->dirtAnimations_.getCurrentAnimation()->resetAnimation();
        this->dirtSpriteSheet->setOffset(offset);
        this->dirtSpriteSheet->setFlipped(this->currentDir_);
    }

    void Lemming::flipSprite()
    {
        this->lemmingSpriteSheet->flipSprite();
        this->dirtSpriteSheet->flipSprite();
        this->setPosition(this->position_);
    }

    HorizontalDirection Lemming::dir() const
    {
        return this->currentDir_;
    }

    void Lemming::setDir(const HorizontalDirection newDir)
    {
        this->currentDir_ = newDir;
    }

    sf::Vector2i Lemming::getActualPos() const
    {
        return {
            static_cast<int>(this->position_.x - TEXTURE_WIDTH / 2 + (this->currentDir_ == 1 ? 1 : 0)),
            static_cast<int>(this->position_.y - TEXTURE_HEIGHT + 1)};
    }

    sf::Vector2i Lemming::getSize() const
    {
        return {static_cast<int>(TEXTURE_WIDTH), static_cast<int>(TEXTURE_HEIGHT)};
    }

    Job Lemming::getCurrentJob() const
    {
        return this->currentJob_;
    }

    bool Lemming::tryAssignJob(const Job job) const
    {
        std::unique_ptr<Engine::IState<Lemming>> state;

        switch (job)
        {
        case Digger:
            if (this->currentJob_ != Walker) return false;
            state = std::make_unique<States::Digger>();
            break;
        case Miner:
            if (this->currentJob_ != Walker) return false;
            state = std::make_unique<States::Miner>();
            break;
        case Blocker:
            if (this->currentJob_ != Walker) return false;
            state = std::make_unique<States::Blocker>();
            break;
        case Builder:
            if (this->currentJob_ != Walker) return false;
            state = std::make_unique<States::Builder>();
            break;
        case Floater:
            if (this->currentJob_ != Walker && this->currentJob_ != Faller) return false;
            state = std::make_unique<States::Floater>();
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

    void Lemming::checkCollisionExit() const
    {
        const sf::Vector2i actualPos = this->position_;
        if (sf::IntRect rect(actualPos.x, actualPos.y, 1, 1); Exit::collisionArea.intersects(rect))
            this->stateMachineManager_->changeState(std::make_unique<States::Winner>());
    }

    void Lemming::win()
    {
        this->winEvent.invoke(this);
    }

    bool Lemming::checkCollision(const int x, const int y, const HorizontalDirection direction) const
    {
        if (x < 0 || x >= this->map_->width() ||
            y < 0 || y >= this->map_->height())
            return false;

        const int index = x + y * this->map_->width();
        
        const Node& node = (*this->map_)[index];
        const HorizontalDirection nodeDir = node.oneWayDirection();

        // defaults to true since every node starts off as non oneway
        bool isOneWayAllowed = true; 
        
        // Check if a direction is specified and compare with node's direction.
        if (direction != None && nodeDir != None) {
            isOneWayAllowed = (nodeDir == direction);
        }
        
        return node.isEnabled() && isOneWayAllowed;
    }

    void Lemming::tryDig(int x, int y) const
    {
        if (x < 0 || x >= this->map_->width() ||
            y < 0 || y >= this->map_->height())
            return;
        
        const int index = x + y * this->map_->width();
        this->map_->changeNode(index, false);
    }

    void Lemming::placeCell(int x, int y, sf::Color color, HorizontalDirection oneWay) const
    {
        if (x < 0 || x >= this->map_->width() ||
            y < 0 || y >= this->map_->height())
        return;
        
        const int index = x + y * this->map_->width();
        this->map_->changeNode(index, true, color, oneWay);
    }
} // Lemmings