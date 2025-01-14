//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings::Engine {

class ModifiableTexture {
private:
    sf::Texture texture_;
    sf::Image image_;
    sf::Sprite sprite_;

public:
    explicit ModifiableTexture(const std::string& fileName);
    void updateTexture();
    sf::Sprite& getSprite();
    sf::Color getPixel(uint x, uint y) const;
    void setPixel(uint x, uint y, const sf::Color& color);
    uint width() const;
    uint height() const;
};

} // Lemmings
