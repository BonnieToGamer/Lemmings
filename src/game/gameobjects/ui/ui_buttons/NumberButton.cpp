//
// Created by filip on 2024-12-26.
//

#include "NumberButton.h"
#include <stdexcept>

namespace Lemmings::UI {
    NumberButton::NumberButton(UI::UIButtonType buttonIndex, uint amount, bool held, float heldTimer, sf::Keyboard::Key shortCutKey) : Button(buttonIndex, held, heldTimer, shortCutKey), amount_(amount)
    {
    }

    void NumberButton::init()
    {
        Button::init();

        if (!this->numberTexture_.loadFromFile(ASSETS_PATH"numbers.png"))
            throw std::runtime_error("Couldn't load texture!");

        this->tensSprite_.setTexture(this->numberTexture_);
        this->onesSprite_.setTexture(this->numberTexture_);
    }

    void NumberButton::update(float delta)
    {
        Button::update(delta);

        const uint tens = this->amount_ > 0 ? this->amount_ / 10 : 10; // 10 is blank
        const uint ones = this->amount_ > 0 ? this->amount_ % 10 : 10;
        this->tensSprite_.setTextureRect({
            static_cast<int>(tens * this->NUMBER_TEXTURE_WIDTH),
            0,
            static_cast<int>(this->NUMBER_TEXTURE_WIDTH),
            static_cast<int>(this->NUMBER_TEXTURE_HEIGHT)
            });
        
        this->onesSprite_.setTextureRect({
            static_cast<int>(ones * this->NUMBER_TEXTURE_WIDTH),
            0,
            static_cast<int>(this->NUMBER_TEXTURE_WIDTH),
            static_cast<int>(this->NUMBER_TEXTURE_HEIGHT)
        });
    }

    void NumberButton::draw(sf::RenderTarget& renderTarget)
    {
        Button::draw(renderTarget);
        renderTarget.draw(this->tensSprite_);
        renderTarget.draw(this->onesSprite_);
    }

    void NumberButton::setPosition(sf::Vector2f pos)
    {
        Button::setPosition(pos);

        const sf::Vector2f spritePos = this->sprite_.getPosition();
        
        this->tensSprite_.setPosition(spritePos + this->NUMBER_OFFSET);
        this->onesSprite_.setPosition(spritePos + this->NUMBER_OFFSET + sf::Vector2f(this->NUMBER_TEXTURE_WIDTH, 0));
    }
} // Lemmings