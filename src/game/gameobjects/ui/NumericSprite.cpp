//
// Created by filip on 2024-12-30.
//

#include "NumericSprite.h"

#include <stdexcept>

#include "../../../engine/Core.h"

namespace Lemmings::UI {
    NumericSprite::NumericSprite(NumberType type) : type_(type)
    {
    }

    void NumericSprite::init()
    {
        this->texture_ = Engine::Core::contentManager->getTexture(this->type_ == Big ? "numbers_big" : "numbers");
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

    sf::Vector2f NumericSprite::getPosition() const
    {
        return this->sprite_.getPosition();
    }

    void NumericSprite::setNumber(Number number)
    {
        if (this->type_ == Big)
            this->sprite_.setTextureRect(sf::IntRect(static_cast<int>(number) * this->NUMBER_BIG_WIDTH, 0, this->NUMBER_BIG_WIDTH, this->NUMBER_BIG_HEIGHT));
        else if (this->type_ == Small)
            this->sprite_.setTextureRect(sf::IntRect(static_cast<int>(number) * this->NUMBER_SMALL_WIDTH, 0, this->NUMBER_SMALL_WIDTH, this->NUMBER_SMALL_HEIGHT));
    }
} // Lemmings