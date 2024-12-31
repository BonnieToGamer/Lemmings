//
// Created by filip on 2024-12-16.
//

#include "AnimatedTexture.h"

#include <utility>

namespace Lemmings::Engine {
    AnimatedTexture::AnimatedTexture(std::shared_ptr<sf::Texture> spriteSheet, sf::Vector2u spriteSize, bool manual) : texture_(std::move(spriteSheet)), elapsed_(0), flipOffset_(0), spriteSize_(spriteSize), manual_(manual)
    {
        this->sprite_.setTexture(*this->texture_);
    }

    void AnimatedTexture::addToTimeline(float time, sf::IntRect rect)
    {
        this->rects_.emplace_back(rect);
        this->timeLine_.emplace_back(time);
    }

    void AnimatedTexture::init()
    {
        this->elapsed_ = 0;
    }

    void AnimatedTexture::update(const float delta)
    {
        if (this->manual_)
            return;
        
        this->elapsed_ += delta;

        int nearestIndex = 0;
        for (int i = 0; i < this->timeLine_.size(); i++)
        {
            if (this->timeLine_[i] <= this->elapsed_ && this->timeLine_[i] > this->timeLine_[nearestIndex])
                nearestIndex = i;
        }

        this->sprite_.setTextureRect(this->rects_[nearestIndex]);
        
        if (this->elapsed_ >= this->timeLine_.back())
            this->elapsed_ = 0.f;
    }

    void AnimatedTexture::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->sprite_);
    }

    void AnimatedTexture::setPosition(int x, int y)
    {
        this->sprite_.setPosition(static_cast<float>(x + this->offset_.x) + this->flipOffset_, static_cast<float>(y + this->offset_.y));
    }

    void AnimatedTexture::flipSprite()
    {
        this->sprite_.setScale(-this->sprite_.getScale().x, this->sprite_.getScale().y);
        this->flipOffset_ = this->sprite_.getScale().x < 0 ? this->spriteSize_.x * std::abs(this->sprite_.getScale().x) : 0.0f;
    }

    void AnimatedTexture::setFlipped(const int dir)
    {
        if ((this->sprite_.getScale().x < 0 && dir < 0) ||
            (this->sprite_.getScale().x > 0 && dir > 0))
            return;

        this->flipSprite();
    }

    void AnimatedTexture::setScale(const float scaleX, const float scaleY)
    {
        this->sprite_.setScale(scaleX, scaleY);
    }

    void AnimatedTexture::nextFrame()
    {
        this->currentFrame_++;
        this->currentFrame_ %= this->timeLine_.size();
        this->sprite_.setTextureRect(this->rects_[this->currentFrame_]);
    }

    void AnimatedTexture::setOffset(sf::Vector2i offset)
    {
        this->offset_ = offset;
    }

    void AnimatedTexture::addSpriteSheetAnim(int amountOfFrames, int yOffset, sf::Vector2i offset, float animationSpeed)
    {
        this->offset_ = offset;
        
        for (int i = 0; i < amountOfFrames; i++)
        {
            this->addToTimeline(
                animationSpeed * i,
                {
                    static_cast<int>(i * this->spriteSize_.x),
                    static_cast<int>(yOffset * this->spriteSize_.y),
                    static_cast<int>(this->spriteSize_.x),
                    static_cast<int>(this->spriteSize_.y)
                }
            );
        }

        this->sprite_.setTextureRect(this->rects_[this->currentFrame_]);
    }
} // Lemmings