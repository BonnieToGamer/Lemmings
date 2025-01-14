//
// Created by filip on 2024-12-26.
//

#include "Button.h"

#include <stdexcept>

#include "../../../../engine/Core.h"
#include "SFML/Graphics/RenderWindow.hpp"

namespace Lemmings::UI {
    Button::Button(UI::UIButtonType buttonIndex, bool held, float heldTimer, sf::Keyboard::Key shortCutKey) : index_(buttonIndex), timer_(heldTimer), held_(held), shortCutKey_(shortCutKey)
    {
    }

    void Button::init()
    {
        this->texture_ = Engine::Core::contentManager->getTexture("buttons");

        this->sprite_.setTexture(*this->texture_);
        this->sprite_.setTextureRect(sf::IntRect(this->BUTTON_WIDTH * this->index_, 0, this->BUTTON_WIDTH, this->BUTTON_HEIGHT));
    }

    void Button::update(float delta)
    {
        sf::RenderWindow* window = Engine::Core::Instance()->getWindow();
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        sf::FloatRect mouseRect(mousePos, {1, 1});
        sf::FloatRect buttonRect(this->sprite_.getPosition(), sf::Vector2f(this->BUTTON_WIDTH, this->BUTTON_HEIGHT));

        if (mouseRect.intersects(buttonRect) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->held_)
            {
                if (this->timer_.update(delta))
                    this->buttonClickEvent.invoke(this->index_);
            }
            else if (!this->isMouseButtonDown_)
                this->buttonClickEvent.invoke(this->index_);
            this->isMouseButtonDown_ = true;
        }
        
        if (this->shortCutKey_ != IGNORE_KEY && (this->held_ ? this->timer_.update(delta) : !this->isMouseButtonDown_) && sf::Keyboard::isKeyPressed(this->shortCutKey_))
        {
            this->buttonClickEvent.invoke(this->index_);
            this->isMouseButtonDown_ = true;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && sf::Keyboard::isKeyPressed(this->shortCutKey_) == false)
            this->isMouseButtonDown_ = false;

    }

    void Button::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->sprite_);
    }

    void Button::setPosition(sf::Vector2f pos)
    {
        this->sprite_.setPosition(pos);
    }

    uint Button::getIndex() const
    {
        return this->index_;
    }
} // Lemmings