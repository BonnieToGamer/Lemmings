//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>
#include <vector>

#include "GameObject.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings::Engine
{
    class AnimatedTexture : public GameObject {
    private:
        std::vector<float> timeLine_;
        std::vector<sf::IntRect> rects_;
        std::shared_ptr<sf::Texture> texture_;
        sf::Sprite sprite_;
        float elapsed_;
        float flipOffset_;
        sf::Vector2u spriteSize_;
        bool manual_;
        int currentFrame_ = 0;
        sf::Vector2u offset_;
        
    public:
        AnimatedTexture(const std::shared_ptr<sf::Texture>& spriteSheet, sf::Vector2u spriteSize, bool manual_);
        void addToTimeline(float time, sf::IntRect rect);
        void init() override;
        void update(float delta) override;
        void draw(sf::RenderTarget& renderTarget) override;
        void setPosition(int x, int y);
        void flipSprite();
        void setScale(float scaleX, float scaleY);
        void nextFrame();

        void addSpriteSheetAnim(int amountOfFrames, int yOffset, sf::Vector2u spriteOffset, float animationSpeed);
    };
}
