//
// Created by filip on 2024-12-30.
//

#pragma once
#include "NumericSprite.h"
#include "../../../engine/Timer.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings::UI {

class TimeDisplay final : public Engine::GameObject {
private:
    uint currentTime_;
    Engine::Timer timer_ = Engine::Timer(1.0f);
    sf::Vector2f position_;
    
    sf::Texture timeWordTexture_;
    sf::Sprite timeWordSprite_;

    NumericSprite* minute_;
    NumericSprite* dash_;
    NumericSprite* secondsTens_;
    NumericSprite* secondsOnes_;

public:
    static constexpr uint WIDTH = NumericSprite::NUMBER_WIDTH * 9;
    
    TimeDisplay(sf::Vector2f position, uint time);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void setTime(uint time);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    void onTimerComplete();
};

} // Lemmigs
