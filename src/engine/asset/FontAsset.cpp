//
// Created by filip on 2025-01-12.
//

#include "FontAsset.h"

#include <stdexcept>

namespace Lemmings::Engine::Asset {
    FontAsset::FontAsset(const std::string& fileName): GameAsset(fileName)
    {
        if (!this->asset_.loadFromFile(ASSETS_PATH + fileName + ".ttf"))
            throw std::runtime_error("Couldn't load font " + fileName + ".ttf");
    }

    sf::Font* FontAsset::getFont()
    {
        return &this->asset_;
    }
} // Lemmings