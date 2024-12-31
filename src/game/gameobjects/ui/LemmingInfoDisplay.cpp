//
// Created by filip on 2024-12-30.
//

#include "LemmingInfoDisplay.h"

#include <stdexcept>

namespace Lemmings::UI {
    LemmingInfoDisplay::LemmingInfoDisplay(uint max) : out_(0), in_(0), max_(max)
    {
    }

    void LemmingInfoDisplay::init()
    {
        this->outTens_.init();
        this->outOnes_.init();
        this->inPercentTens_.init();
        this->inPercentOnes_.init();

        if (!this->reservedWordsTexture_.loadFromFile(ASSETS_PATH"reserved_words.png"))
            throw std::runtime_error("Could not load reserved_words.png");

        this->outWordSprite_.setTexture(this->reservedWordsTexture_);
        this->inWordSprite_.setTexture(this->reservedWordsTexture_);
        this->outWordSprite_.setTextureRect({0, 15, 24, 15});
        this->inWordSprite_.setTextureRect({0, 0, 16, 15});

    }

    void LemmingInfoDisplay::update(float delta)
    {
        if (this->out_ < 10)
        {
            this->outOnes_.setNumber(NumericSprite::Empty);
            this->outTens_.setNumber(static_cast<NumericSprite::Number>(this->out_));
        }

        else
        {
            this->outOnes_.setNumber(static_cast<NumericSprite::Number>(this->out_ % 10));
            this->outTens_.setNumber(static_cast<NumericSprite::Number>(this->out_ / 10));
        }

        if (this->in_ < 10)
        {
            this->inPercentOnes_.setNumber(NumericSprite::Empty);
            this->inPercentTens_.setNumber(static_cast<NumericSprite::Number>(this->in_));
        }

        else
        {
            this->inPercentOnes_.setNumber(static_cast<NumericSprite::Number>(this->out_ % 10));
            this->inPercentTens_.setNumber(static_cast<NumericSprite::Number>(this->out_ / 10));
        }
    }

    void LemmingInfoDisplay::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->outWordSprite_);
        renderTarget.draw(this->inWordSprite_);
        this->outTens_.draw(renderTarget);
        this->outOnes_.draw(renderTarget);
        this->inPercentTens_.draw(renderTarget);
        this->inPercentOnes_.draw(renderTarget);
    }

    void LemmingInfoDisplay::setPosition(sf::Vector2f pos)
    {
        this->position_ = pos;

        this->outWordSprite_.setPosition(this->position_);
        this->outTens_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 4, 0));
        this->outOnes_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 5, 0));
        this->inWordSprite_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 9, 0));
        this->inPercentTens_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 12, 0));
        this->inPercentOnes_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 13, 0));
    }

    sf::Vector2f LemmingInfoDisplay::getPosition()
    {
        return this->position_;
    }
} // Lemmings