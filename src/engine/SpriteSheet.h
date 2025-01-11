//
// Created by filip on 2025-01-06.
//

#pragma once
#include "GameObject.h"
#include "SFML/Graphics/Sprite.hpp"

namespace Lemmings::Engine {

class SpriteSheet : public GameObject {
private:
    sf::Vector2u spriteSize_;

    sf::Texture* texture_;
    sf::Sprite sprite_;

    std::string textureName_;
    
    float flipOffset_ = 0;
    sf::Vector2f position_;
    sf::Vector2i offset_;

public:
    SpriteSheet(sf::Vector2u spriteSize, sf::Texture* texture);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void setCurrentSprite(uint x, uint y);
    void setPosition(int x, int y);
    void flipSprite();
    void setFlipped(int dir);
    void setScale(float scaleX, float scaleY);
    void setOffset(sf::Vector2i offset);
    void setColor(sf::Color color);
};

} // Lemmings
