//
// Created by filip on 2024-12-30.
//

#pragma once
#include "NumericSprite.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings::UI {

class LemmingInfoDisplay final : public Engine::GameObject {
private:
    uint out_;
    uint in_;
    uint max_;
    sf::Vector2f position_;
    sf::Texture reservedWordsTexture_;
    sf::Sprite outWordSprite_;
    sf::Sprite inWordSprite_;

    NumericSprite outTens_;
    NumericSprite outOnes_;

    NumericSprite inPercentTens_;
    NumericSprite inPercentOnes_;

public:
    LemmingInfoDisplay(uint max);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
};

} // Lemmings