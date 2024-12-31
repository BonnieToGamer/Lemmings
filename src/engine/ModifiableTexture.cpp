//
// Created by filip on 2024-12-16.
//

#include "ModifiableTexture.h"

#include <stdexcept>

namespace Lemmings::Engine {
    ModifiableTexture::ModifiableTexture(const std::string& fileName) : texture_(), sprite_()
    {
        if (!this->image_.loadFromFile(fileName))
            throw std::runtime_error("Couldn't load texture!");

        this->texture_.loadFromImage(this->image_);
        this->sprite_.setTexture(this->texture_);
    }

    void ModifiableTexture::updateTexture()
    {
        this->texture_.update(this->image_);
        // this->sprite_.setTexture(this->texture_);
    }

    sf::Sprite& ModifiableTexture::getSprite()
    {
        return this->sprite_;
    }

    sf::Color ModifiableTexture::getPixel(const uint x, const uint y)
    {
        return this->image_.getPixel(x, y);
    }

    void ModifiableTexture::setPixel(uint x, uint y, const sf::Color& color)
    {
        this->image_.setPixel(x, y, color);
    }

    uint ModifiableTexture::width()
    {
        return this->texture_.getSize().x;
    }

    uint ModifiableTexture::height()
    {
        return this->texture_.getSize().y;
    }
} // Lemmings