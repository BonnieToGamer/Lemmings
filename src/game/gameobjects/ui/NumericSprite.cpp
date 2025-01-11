//
// Created by filip on 2024-12-30.
//

#include "NumericSprite.h"

#include <stdexcept>

#include "../../../engine/Core.h"

namespace Lemmings::UI {
    
    void NumericSprite::init()
    {
        this->texture_ = Engine::Core::contentManager->getTexture("numbers_big");
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

    sf::Vector2f NumericSprite::getPosition()
    {
        return this->sprite_.getPosition();
    }

    void NumericSprite::setNumber(Number number)
    {
        this->sprite_.setTextureRect(sf::IntRect(static_cast<int>(number) * this->NUMBER_WIDTH, 0, this->NUMBER_WIDTH, this->NUMBER_HEIGHT));
    }
} // Lemmings