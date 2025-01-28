//
// Created by filip on 2024-12-26.
//

#pragma once
#include "../../../../engine/Event.h"
#include "../../../../engine/GameObject.h"
#include "../../../../engine/Timer.h"
#include "../UIButtonType.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"

namespace Lemmings::UI {

class Button : public Engine::GameObject {
protected:
    sf::Texture* texture_;
    sf::Sprite sprite_;
    UI::UIButtonType index_;
    Engine::Timer timer_;
    bool held_;
    bool isMouseButtonDown_ = false;
    sf::Keyboard::Key shortCutKey_;
    
    static constexpr sf::Keyboard::Key IGNORE_KEY = sf::Keyboard::Apostrophe;
    
public:
    static const unsigned int BUTTON_WIDTH = 16;
    static const unsigned int BUTTON_HEIGHT = 23;
    
    Engine::Event<UI::UIButtonType> buttonClickEvent;

    Button(UI::UIButtonType buttonIndex, bool held, float heldTimer = 0.0f, sf::Keyboard::Key shortCutKey = IGNORE_KEY);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    virtual void setPosition(sf::Vector2f pos);
    unsigned int getIndex() const;
};

} // Lemmings
