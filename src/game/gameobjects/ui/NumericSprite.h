//
// Created by filip on 2024-12-30.
//

#pragma once
#include <memory>

#include "../../../engine/GameObject.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings::UI {

class NumericSprite final : public Engine::GameObject {
public:
    enum Number
    {
        Zero = 0,
        One = 1,
        Two = 2,
        Three = 3,
        Four = 4,
        Five = 5,
        Six = 6,
        Seven = 7,
        Eight = 8,
        Nine = 9,
        Dash = 10,
        Percent = 11,
        Empty = 12
    };

private:
    sf::Sprite sprite_;
    sf::Texture* texture_ = nullptr;
    
public:
    static constexpr uint NUMBER_WIDTH = 8;
    static constexpr uint NUMBER_HEIGHT = 16;
    
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
    void setNumber(Number number);
};

} // Lemmings
