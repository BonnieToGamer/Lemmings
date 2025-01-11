//
// Created by filip on 2025-01-09.
//

#pragma once
#include "GameAsset.h"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings::Engine::Asset {

class TextureAsset final : public GameAsset {
private:
    sf::Texture asset_;
    
public:
    explicit TextureAsset(const std::string& fileName);
    sf::Texture* getTexture();
};

} // Lemmings
