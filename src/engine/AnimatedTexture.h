//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>
#include <vector>

#include "GameObject.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings::Engine
{
    class AnimatedTexture : public GameObject {
    private:
        std::vector<std::shared_ptr<sf::Texture>> textures_;
        std::vector<float> timeLine_;
        sf::Sprite sprite_;
        float elapsed_;
        
    public:
        AnimatedTexture();
        void addToTimeline(float time, const std::shared_ptr<sf::Texture>& texture);
        void init() override;
        void update(float delta) override;
        void draw(sf::RenderTexture& renderTexture) override;
        void setPosition(int x, int y);
    };
}
