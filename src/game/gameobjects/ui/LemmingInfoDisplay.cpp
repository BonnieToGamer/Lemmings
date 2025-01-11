//
// Created by filip on 2024-12-30.
//

#include "LemmingInfoDisplay.h"

#include <stdexcept>

#include "../../../engine/Core.h"

namespace Lemmings::UI {
    LemmingInfoDisplay::LemmingInfoDisplay(uint max) : out_(0), in_(0), max_(max)
    {
    }

    void LemmingInfoDisplay::init()
    {
        this->outSprite_.init();
        this->inSprite_.init();

        this->reservedWordsTexture_ = Engine::Core::contentManager->getTexture("reserved_words");

        this->outWordSprite_.setTexture(*this->reservedWordsTexture_);
        this->inWordSprite_.setTexture(*this->reservedWordsTexture_);
        this->outWordSprite_.setTextureRect({0, 15, 24, 15});
        this->inWordSprite_.setTextureRect({0, 0, 16, 15});

    }

    void LemmingInfoDisplay::update(float delta)
    {
        this->inSprite_.setValue(this->in_);
        this->outSprite_.setValue(this->out_);
    }

    void LemmingInfoDisplay::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->outWordSprite_);
        renderTarget.draw(this->inWordSprite_);
        this->outSprite_.draw(renderTarget);
        this->inSprite_.draw(renderTarget);
    }

    void LemmingInfoDisplay::setPosition(sf::Vector2f pos)
    {
        this->position_ = pos;

        this->outWordSprite_.setPosition(this->position_);
        this->outSprite_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 4, 0));
        this->inWordSprite_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 9, 0));
        this->inSprite_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 12, 0));
    }

    sf::Vector2f LemmingInfoDisplay::getPosition()
    {
        return this->position_;
    }

    void LemmingInfoDisplay::setAmountOut(uint out)
    {
        this->out_ = out;
    }

    void LemmingInfoDisplay::setAmountIn(uint in)
    {
        this->in_ = in;
    }
} // Lemmings