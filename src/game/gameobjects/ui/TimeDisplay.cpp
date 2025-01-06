//
// Created by filip on 2024-12-30.
//

#include "TimeDisplay.h"

#include <stdexcept>

namespace Lemmings::UI {
    TimeDisplay::TimeDisplay(sf::Vector2f position, uint time): currentTime_(time), position_(position)
    {
        
    }

    void TimeDisplay::init()
    {
        auto minute = std::make_unique<NumericSprite>();
        auto dash = std::make_unique<NumericSprite>();
        auto secondsTens = std::make_unique<NumericSprite>();
        auto secondsOnes = std::make_unique<NumericSprite>();

        // ReSharper gives error "The address of the local variable 'minute/dash/etc' may escape the function"
        // I don't understand why as the underlying pointer is still the same.
        // So I'm just going to disable the warning as it is annoying me :P
        
        // ReSharper disable CppDFALocalValueEscapesFunction
        this->minute_ = minute.get();
        this->dash_ = dash.get();
        this->secondsTens_ = secondsTens.get();
        this->secondsOnes_ = secondsOnes.get();
        // ReSharper enable CppDFALocalValueEscapesFunction

        this->addChild(std::move(minute));
        this->addChild(std::move(dash));
        this->addChild(std::move(secondsTens));
        this->addChild(std::move(secondsOnes));
        

        if (!this->timeWordTexture_.loadFromFile(ASSETS_PATH"reserved_words.png"))
            throw std::runtime_error("Couldn't load reserved_words.png");

        this->timeWordSprite_.setTexture(this->timeWordTexture_);
        this->timeWordSprite_.setTextureRect({0, 32, 32, 15});

        this->timer_.onTimerCompleteEvent += [this] { this->onTimerComplete(); };

        GameObject::init();
        this->dash_->setNumber(NumericSprite::Dash);
    }

    void TimeDisplay::update(float delta)
    {
        this->timer_.update(delta);
        this->minute_->setNumber(static_cast<NumericSprite::Number>(this->currentTime_ / 60));

        uint seconds = this->currentTime_ % 60;
        this->secondsTens_->setNumber(static_cast<NumericSprite::Number>(seconds / 10));
        this->secondsOnes_->setNumber(static_cast<NumericSprite::Number>(seconds % 10));
        GameObject::update(delta);
    }

    void TimeDisplay::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->timeWordSprite_);
        GameObject::draw(renderTarget);
    }

    void TimeDisplay::setTime(uint time)
    {
        this->currentTime_ = time;
    }

    void TimeDisplay::setPosition(sf::Vector2f position)
    {
        this->position_ = position;
        
        this->timeWordSprite_.setPosition(this->position_);
        this->minute_->setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 5, 0));
        this->dash_->setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 6, 0));
        this->secondsTens_->setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 7, 0));
        this->secondsOnes_->setPosition(this->position_ + sf::Vector2f(NumericSprite::NUMBER_WIDTH * 8, 0));
        
    }

    sf::Vector2f TimeDisplay::getPosition()
    {
        return this->position_;
    }

    void TimeDisplay::onTimerComplete()
    {
        if (this->currentTime_ == 0)
            return;
        
        this->currentTime_--;
    }
} // Lemmigs