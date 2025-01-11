//
// Created by filip on 2025-01-09.
//

#pragma once
#include <string>
#include <unordered_map>

#include "GameAsset.h"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings::Engine::Asset {

class ContentManager {
private:
    std::unordered_map<std::string, std::shared_ptr<GameAsset>> assets_;

public:
    ~ContentManager();
    
    sf::Texture* getTexture(const std::string& fileName);
};

} // Lemmings
