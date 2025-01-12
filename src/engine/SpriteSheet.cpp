//
// Created by filip on 2025-01-06.
//

#include "SpriteSheet.h"

#include <stdexcept>

namespace Lemmings::Engine {
    SpriteSheet::SpriteSheet(sf::Vector2u spriteSize, sf::Texture* texture) : spriteSize_(spriteSize), texture_(texture) { }

    void SpriteSheet::init()
    {
        this->sprite_.setTexture(*this->texture_);
        this->setCurrentSprite(0, 0);
        GameObject::init();
    }

    void SpriteSheet::update(float delta) { }

    void SpriteSheet::draw(sf::RenderTarget& renderTarget)
    {
        this->sprite_.setPosition(this->position_ + sf::Vector2f(this->offset_));
        renderTarget.draw(this->sprite_);
    }

    void SpriteSheet::setCurrentSprite(uint x, uint y)
    {
        this->sprite_.setTextureRect(sf::IntRect(x * this->spriteSize_.x, y * this->spriteSize_.y, this->spriteSize_.x, this->spriteSize_.y));
    }

    void SpriteSheet::setPosition(int x, int y)
    {
        this->position_ = sf::Vector2f(x + this->flipOffset_, y);
    }

    void SpriteSheet::flipSprite()
    {
        this->sprite_.setScale(-this->sprite_.getScale().x, this->sprite_.getScale().y);
        this->flipOffset_ = this->sprite_.getScale().x < 0 ? this->spriteSize_.x * std::abs(this->sprite_.getScale().x) : 0.0f;
    }

    void SpriteSheet::setFlipped(int dir)
    {
        if ((this->sprite_.getScale().x < 0 && dir < 0) ||
            (this->sprite_.getScale().x > 0 && dir > 0))
            return;

        this->flipSprite();
    }

    void SpriteSheet::setScale(float scaleX, float scaleY)
    {
        this->sprite_.setScale(scaleX, scaleY);
    }

    void SpriteSheet::setOffset(sf::Vector2i offset)
    {
        this->offset_ = offset;
    }

    sf::Vector2i SpriteSheet::getOffset() const
    {
        return this->offset_;
    }

    void SpriteSheet::setColor(sf::Color color)
    {
        this->sprite_.setColor(color);
    }
} // Lemmings