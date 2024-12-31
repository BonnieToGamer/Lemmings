//
// Created by filip on 2024-12-31.
//

#include "DualNumericSprite.h"

namespace Lemmings::UI {
    void DualNumericSprite::init()
    {
        this->tens_.init();
        this->ones_.init();
    }

    void DualNumericSprite::update(float delta)
    {
    }

    void DualNumericSprite::draw(sf::RenderTarget& renderTarget)
    {
        this->tens_.draw(renderTarget);
        this->ones_.draw(renderTarget);
    }

    void DualNumericSprite::setValue(uint value)
    {
        if (value >= 10)
        {
            this->tens_.setNumber(static_cast<NumericSprite::Number>(value / 10));
            this->ones_.setNumber(static_cast<NumericSprite::Number>(value % 10));
        }
        else
        {
            this->tens_.setNumber(static_cast<NumericSprite::Number>(value % 10));
            this->ones_.setNumber(NumericSprite::Number::Empty);
        }
    }

    void DualNumericSprite::setEmpty()
    {
        this->tens_.setNumber(NumericSprite::Number::Empty);
        this->ones_.setNumber(NumericSprite::Number::Empty);
    }

    void DualNumericSprite::setPosition(sf::Vector2f pos)
    {
        this->tens_.setPosition(pos);
        this->ones_.setPosition(pos + sf::Vector2f(NumericSprite::NUMBER_WIDTH, 0));
    }

    sf::Vector2f DualNumericSprite::getPosition()
    {
        return this->tens_.getPosition();
    }
} // Lemmings