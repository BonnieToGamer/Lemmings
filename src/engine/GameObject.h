//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>
#include "SFML/Graphics/RenderTexture.hpp"

namespace Lemmings::Engine {

class GameObject {
private:
    std::vector<std::unique_ptr<GameObject>> children_;
    
public:
    virtual ~GameObject() = default;
    virtual void init();
    virtual void update(float delta);
    virtual void draw(sf::RenderTarget& renderTarget);
    
    void addChild(std::unique_ptr<GameObject> child);
    void removeChild(std::unique_ptr<GameObject> child);
};
} // Lemmings
