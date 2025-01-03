//
// Created by filip on 2024-12-26.
//

#pragma once
#include "Button.h"

namespace Lemmings::UI {

class NumberButton : public Button {
private:
    sf::Texture numberTexture_;
    sf::Sprite tensSprite_;
    sf::Sprite onesSprite_;

    const uint NUMBER_TEXTURE_WIDTH = 4;
    const uint NUMBER_TEXTURE_HEIGHT = 8;
    const sf::Vector2f NUMBER_OFFSET = {3, 1};

protected:
    uint amount_;
    
public:
    NumberButton(UI::UIButtonType buttonIndex, uint amount, bool held, float heldTimer = 0.0f, sf::Keyboard::Key shortCutKey = IGNORE_KEY);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void setPosition(sf::Vector2f pos) override;
    void setAmount(uint amount);
};

} // Lemmings
