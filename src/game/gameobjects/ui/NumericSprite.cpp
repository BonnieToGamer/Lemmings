//
// Created by filip on 2024-12-30.
//

#include "NumericSprite.h"

#include <stdexcept>

namespace Lemmings {
    std::unique_ptr<sf::Texture> NumericSprite::texture_;
    
    void NumericSprite::init()
    {
        if (texture_ == nullptr)
        {
            texture_ = std::make_unique<sf::Texture>();
            if(!texture_->loadFromFile(ASSETS_PATH"numbers_big.png"))
                throw std::runtime_error("Couldn't load numbers_big.png");
        }

        this->sprite_.setTexture(*texture_);
        this->setNumber(Zero);
    }

    void NumericSprite::update(float delta) { }

    void NumericSprite::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->sprite_);
    }

    void NumericSprite::setPosition(sf::Vector2f pos)
    {
        this->sprite_.setPosition(pos.x, pos.y);
    }

    void NumericSprite::setNumber(Number number)
    {
        this->sprite_.setTextureRect(sf::IntRect(static_cast<int>(number) * this->NUMBER_WIDTH, 0, this->NUMBER_WIDTH, this->NUMBER_HEIGHT));
    }

    void NumericSprite::destroyTextures()
    {
        texture_ = nullptr;
    }
} // Lemmings