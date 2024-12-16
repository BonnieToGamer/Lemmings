//
// Created by filip on 2024-12-16.
//

#include "AnimatedTexture.h"

namespace Lemmings::Engine {
    AnimatedTexture::AnimatedTexture() : elapsed_(0), sprite_() { }

    void AnimatedTexture::addToTimeline(float time, const std::shared_ptr<sf::Texture>& texture)
    {
        this->textures_.emplace_back(texture);
        this->timeLine_.emplace_back(time);
    }

    void AnimatedTexture::init()
    {
        this->elapsed_ = 0;
    }

    void AnimatedTexture::update(float delta)
    {
        elapsed_ += delta;

        int nearestIndex = 0;
        for (int i = 0; i < this->timeLine_.size(); i++)
        {
            if (this->timeLine_[i] <= this->elapsed_ && this->timeLine_[i] > this->timeLine_[nearestIndex])
                nearestIndex = i;
        }

        this->sprite_.setTexture(*this->textures_[nearestIndex].get());
        
        if (this->elapsed_ >= this->timeLine_.back())
            this->elapsed_ = 0.f;
    }

    void AnimatedTexture::draw(sf::RenderTexture& renderTexture)
    {
        renderTexture.draw(this->sprite_);
    }

    void AnimatedTexture::setPosition(int x, int y)
    {
        this->sprite_.setPosition(x, y);
    }

} // Lemmings