//
// Created by filip on 2025-01-09.
//

#include "ContentManager.h"

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
            auto asset = std::make_shared<TextureAsset>(fileName);
            this->assets_[fileName] = asset;
            return asset->getTexture();
        }

        auto asset = std::dynamic_pointer_cast<TextureAsset>(this->assets_[fileName]);
        return asset ? asset->getTexture() : nullptr;
    }
} // Lemmings