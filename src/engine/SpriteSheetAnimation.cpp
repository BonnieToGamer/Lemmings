//
// Created by filip on 2025-01-06.
//

#include "SpriteSheetAnimation.h"

namespace Lemmings::Engine {
    SpriteSheetAnimation::SpriteSheetAnimation(SpriteSheet* spriteSheet, AnimationDirection dir, unsigned int amountOfFrames, sf::Vector2u offset) : spriteSheet_(spriteSheet), animationDir_(dir), maxFrames_(amountOfFrames), offset_(offset)
    {
    }

    void SpriteSheetAnimation::nextFrame()
    {
        this->currentFrame_ = ++this->currentFrame_ % this->maxFrames_;

        switch (this->animationDir_)
        {
        case Right:
                this->spriteSheet_->setCurrentSprite(this->currentFrame_ * (this->offset_.x == 0 ? 1: this->offset_.x), this->offset_.y);
                break;

            case Down:
                this->spriteSheet_->setCurrentSprite(this->offset_.x, this->currentFrame_ * this->offset_.y);
                break;

            default:
                break;
        }
    }

    void SpriteSheetAnimation::resetAnimation()
    {
        this->currentFrame_ = -1;
        this->nextFrame();
    }
} // Lemmings