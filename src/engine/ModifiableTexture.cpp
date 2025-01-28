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
    }

    sf::Sprite& ModifiableTexture::getSprite()
    {
        return this->sprite_;
    }

    sf::Color ModifiableTexture::getPixel(const unsigned int x, const unsigned int y) const
    {
        return this->image_.getPixel(x, y);
    }

    void ModifiableTexture::setPixel(unsigned int x, unsigned int y, const sf::Color& color)
    {
        this->image_.setPixel(x, y, color);
    }

    unsigned int ModifiableTexture::width() const
    {
        return this->texture_.getSize().x;
    }

    unsigned int ModifiableTexture::height() const
    {
        return this->texture_.getSize().y;
    }
} // Lemmings