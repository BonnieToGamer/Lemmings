//
// Created by filip on 2024-12-16.
//

#pragma once
#include "SFML/Graphics/RenderTexture.hpp"

namespace Lemmings::Engine {

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void init() = 0;
    virtual void update(float delta) = 0;
    virtual void draw(sf::RenderTarget& renderTarget) = 0;
};

} // Lemmings
