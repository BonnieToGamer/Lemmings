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
    sf::Color getPixel(unsigned int x, unsigned int y) const;
    void setPixel(unsigned int x, unsigned int y, const sf::Color& color);
    unsigned int width() const;
    unsigned int height() const;
};

} // Lemmings
