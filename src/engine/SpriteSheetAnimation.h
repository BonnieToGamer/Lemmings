//
// Created by filip on 2025-01-06.
//

#pragma once
#include "SpriteSheet.h"
#include "SFML/Graphics/Sprite.hpp"

namespace Lemmings::Engine {

class SpriteSheetAnimation {
public:
    enum AnimationDirection
    {
        Down,
        Right
    };
    
private:
    SpriteSheet* spriteSheet_;
    AnimationDirection animationDir_;
    unsigned int maxFrames_;
    unsigned int currentFrame_ = 0;
    sf::Vector2u offset_;

public:
    SpriteSheetAnimation(SpriteSheet* spriteSheet, AnimationDirection dir, unsigned int amountOfFrames, sf::Vector2u offset);
    void nextFrame();
    void resetAnimation();
};

} // Lemmings
