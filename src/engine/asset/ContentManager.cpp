//
// Created by filip on 2025-01-09.
//

#include "ContentManager.h"

#include "FontAsset.h"
#include "TextureAsset.h"

namespace Lemmings::Engine::Asset {
    ContentManager::~ContentManager()
    {
        for (auto& pair : this->assets_)
            pair.second = nullptr;
    }

    sf::Texture* ContentManager::getTexture(const std::string& fileName)
    {
        if (this->assets_.find(fileName) == this->assets_.end())
        {
            const auto asset = std::make_shared<TextureAsset>(fileName);
            this->assets_[fileName] = asset;
            return asset->getTexture();
        }

        const auto asset = std::dynamic_pointer_cast<TextureAsset>(this->assets_[fileName]);
        return asset ? asset->getTexture() : nullptr;
    }

    sf::Font* ContentManager::getFont(const std::string& fileName)
    {
        if (this->assets_.find(fileName) == this->assets_.end())
        {
            const auto asset = std::make_shared<FontAsset>(fileName);
            this->assets_[fileName] = asset;
            return asset->getFont();
        }

        const auto asset = std::dynamic_pointer_cast<FontAsset>(this->assets_[fileName]);
        return asset ? asset->getFont() : nullptr;
    }
} // Lemmings