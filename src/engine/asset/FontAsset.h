//
// Created by filip on 2025-01-12.
//

#pragma once
#include "GameAsset.h"
#include "SFML/Graphics/Font.hpp"

namespace Lemmings::Engine::Asset {

class FontAsset final : public GameAsset {
private:
    sf::Font asset_;

public:
    explicit FontAsset(const std::string& fileName);
    sf::Font* getFont();
};

} // Lemmings
