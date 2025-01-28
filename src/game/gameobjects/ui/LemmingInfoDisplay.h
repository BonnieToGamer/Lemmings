//
// Created by filip on 2024-12-30.
//

#pragma once
#include "DualNumericSprite.h"
#include "NumericSprite.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings::UI {

class LemmingInfoDisplay final : public Engine::GameObject {
private:
    unsigned int out_;
    unsigned int in_;
    unsigned int max_;
    sf::Vector2f position_;
    sf::Texture* reservedWordsTexture_;
    sf::Sprite outWordSprite_;
    sf::Sprite inWordSprite_;

    DualNumericSprite outSprite_;
    DualNumericSprite inSprite_;

public:
    LemmingInfoDisplay(unsigned int max);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
    void setAmountOut(unsigned int out);
    void setAmountIn(unsigned int in);
};

} // Lemmings
