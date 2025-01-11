//
// Created by filip on 2025-01-09.
//

#include "TextureAsset.h"
#include <stdexcept>

namespace Lemmings::Engine::Asset {
    TextureAsset::TextureAsset(const std::string& fileName) : GameAsset(fileName)
    {
        if (!this->asset_.loadFromFile(ASSETS_PATH + fileName + ".png"))
            throw std::runtime_error("Couldn't load texture " + fileName + ".png");
    }

    sf::Texture* TextureAsset::getTexture()
    {
        return &this->asset_;
    }
} // Lemmings