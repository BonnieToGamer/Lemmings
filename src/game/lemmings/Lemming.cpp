//
// Created by filip on 2024-12-16.
//

#include "Lemming.h"

#include <complex.h>
#include <stdexcept>

#include "SFML/Graphics/RectangleShape.hpp"
#include "states/Walker.h"

namespace Lemmings {
    Lemming::Lemming(const std::shared_ptr<Map>& map) : map_(map) { }

    void Lemming::init()
    {
        this->stateMachineManager_ =
            std::make_unique<Engine::StateMachineManager<Lemming>>(std::make_shared<States::Walker>(), this->shared_from_this());


        const auto lemmingTexture = std::make_shared<sf::Texture>();
        
        if (!lemmingTexture->loadFromFile(ASSETS_PATH"lemming.png"))
            throw std::runtime_error("Couldn't load texture!");

        sf::Vector2u spriteSize(TEXTURE_WIDTH, TEXTURE_HEIGHT);
        auto walkerAnim = std::make_shared<Engine::AnimatedTexture>(lemmingTexture, spriteSize, true);
        auto fallerAnim = std::make_shared<Engine::AnimatedTexture>(lemmingTexture, spriteSize, true);
        auto diggerAnim = std::make_shared<Engine::AnimatedTexture>(lemmingTexture, spriteSize, true);

        walkerAnim->addSpriteSheetAnim(8, 0, {0, 0}, 0);
        fallerAnim->addSpriteSheetAnim(4, 1, {0, 1}, 0);
        diggerAnim->addSpriteSheetAnim(15, 2, {0, 2}, 0);
        
        this->animations_.emplace(Job::Walker, walkerAnim);
        this->animations_.emplace(Job::Faller, fallerAnim);
        this->animations_.emplace(Job::Digger, diggerAnim);
        this->currentAnimatedTexture_ = walkerAnim;
    }

    void Lemming::update(float delta)
    {
        this->currentAnimatedTexture_->nextFrame();
        this->stateMachineManager_->update(delta);
    }

    void Lemming::draw(sf::RenderTarget& renderTarget)
    {
        this->currentAnimatedTexture_->setPosition(this->position_.x - TEXTURE_WIDTH / 2 + (this->currentDir_ == 1 ? 1 : 0),
                                                   this->position_.y - TEXTURE_HEIGHT + 1);
        this->currentAnimatedTexture_->draw(renderTarget);
        
        sf::RectangleShape rectShape(sf::Vector2f(1.0f, 1.0f));
        rectShape.setFillColor(sf::Color::Green);
        rectShape.setPosition(this->position_.x, this->position_.y);
        renderTarget.draw(rectShape);
    }

    const sf::Vector2f& Lemming::getPosition()
    {
        return this->position_;
    }

    void Lemming::setPosition(const sf::Vector2f& newPos)
    {
        this->position_ = newPos;
    }

    const std::shared_ptr<Map>& Lemming::map()
    {
        return this->map_;
    }

    void Lemming::playAnimation(Job job)
    {
        if (const auto itr = this->animations_.find(job); itr == this->animations_.end())
            return;
            
        this->currentAnimatedTexture_ = this->animations_[job];
        this->currentAnimatedTexture_->init();
    }

    void Lemming::flipSprite() const
    {
        this->currentAnimatedTexture_->flipSprite();
    }

    bool Lemming::checkCollision(const float x, const float y) const
    {
        if (x < 0 || x >= static_cast<float>(this->map_->width()) ||
            y < 0 || y >= static_cast<float>(this->map_->height()))
            return true;

        const int index = static_cast<int>(x) + static_cast<int>(y) * this->map_->width();
        return (*this->map_)[index].isEnabled();
    }

    int Lemming::dir() const
    {
        return this->currentDir_;
    }

    void Lemming::setDir(const int newDir)
    {
        this->currentDir_ = newDir;
    }
} // Lemmings