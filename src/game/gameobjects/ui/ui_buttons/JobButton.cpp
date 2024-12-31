//
// Created by filip on 2024-12-26.
//

#include "JobButton.h"

#include "SFML/Graphics/RectangleShape.hpp"

namespace Lemmings::UI {
    JobButton::JobButton(UI::UIButtonType buttonIndex, uint amount, bool held, Job job, float heldTimer, sf::Keyboard::Key shortCutKey) : NumberButton(buttonIndex, amount, held, heldTimer, shortCutKey), job_(job), selected_(false)
    {
    }

    void JobButton::init()
    {
        NumberButton::init();
    }

    void JobButton::update(float delta)
    {
        NumberButton::update(delta);
    }

    void JobButton::draw(sf::RenderTarget& renderTarget)
    {
        NumberButton::draw(renderTarget);

        if (!this->selected_)
            return;

        sf::RectangleShape selectRect({static_cast<float>(this->BUTTON_WIDTH), static_cast<float>(this->BUTTON_HEIGHT)});
        selectRect.setPosition(this->sprite_.getPosition());
        selectRect.setFillColor(sf::Color::Transparent);
        selectRect.setOutlineColor(sf::Color::White);
        selectRect.setOutlineThickness(-1.0f);
        renderTarget.draw(selectRect);
    }

    void JobButton::setPosition(sf::Vector2f pos)
    {
        NumberButton::setPosition(pos);
    }

    void JobButton::setSelected(bool selected)
    {
        this->selected_ = selected;
    }

    Job JobButton::getJob() const
    {
        return this->job_;
    }

    void JobButton::decreaseAmount()
    {
        this->amount_--;
    }
} // Lemmings