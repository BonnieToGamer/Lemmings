//
// Created by filip on 2024-12-30.
//

#include "TimeDisplay.h"

#include <stdexcept>

namespace Lemmings::UI {
    TimeDisplay::TimeDisplay(sf::Vector2f position): currentTime_(0), position_(position)
    {
        
    }

    void TimeDisplay::init()
    {
        this->currentTime_ = 0;
        this->minute_.init();
        this->dash_.init();
        this->secondsTens_.init();
        this->secondsOnes_.init();
        
        this->dash_.setNumber(NumericSprite::Dash);

        if (!this->timeWordTexture_.loadFromFile(ASSETS_PATH"reserved_words.png"))
            throw std::runtime_error("Couldn't load reserved_words.png");

        this->timeWordSprite_.setTexture(this->timeWordTexture_);
        this->timeWordSprite_.setTextureRect({0, 32, 32, 15});
    }

    void TimeDisplay::update(float delta)
    {
        if (this->timer_.update(delta) && this->currentTime_ != 0)
            this->currentTime_--;

        this->minute_.setNumber(static_cast<NumericSprite::Number>(this->currentTime_ / 60));

        uint seconds = this->currentTime_ % 60;
        this->secondsTens_.setNumber(static_cast<NumericSprite::Number>(seconds / 10));
        this->secondsOnes_.setNumber(static_cast<NumericSprite::Number>(seconds % 10));
    }

    void TimeDisplay::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->timeWordSprite_);
        this->minute_.draw(renderTarget);
        this->dash_.draw(renderTarget);
        this->secondsTens_.draw(renderTarget);
        this->secondsOnes_.draw(renderTarget);
    }

    void TimeDisplay::setTime(uint time)
    {
        this->currentTime_ = time;
    }

    void TimeDisplay::setPosition(sf::Vector2f position)
    {
        this->position_ = position;
        
        this->timeWordSprite_.setPosition(this->position_);
        this->minute_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 5, 0));
        this->dash_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 6, 0));
        this->secondsTens_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 7, 0));
        this->secondsOnes_.setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 8, 0));
        
    }

    sf::Vector2f TimeDisplay::getPosition()
    {
        return this->position_;
    }
} // Lemmigs