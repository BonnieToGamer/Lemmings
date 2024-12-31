//
// Created by filip on 2024-12-31.
//

#pragma once
#include "NumericSprite.h"

namespace Lemmings::UI {

class DualNumericSprite : public Engine::GameObject {
private:
    NumericSprite tens_;
    NumericSprite ones_;
    
public:
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void setValue(uint value);
    void setEmpty();
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
};

} // Lemmings
