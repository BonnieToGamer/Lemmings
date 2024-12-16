//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>

#include "SceneManager.h"
#include "SFML/Graphics.hpp"

namespace Lemmings::Engine
{
    class Core {
    private:
        std::unique_ptr<sf::RenderWindow> renderWindow_;
        SceneManager sceneManager_;
        sf::RenderTexture renderTexture_;
        sf::Sprite renderSprite_;
        const uint DESIGNED_RESOLUTION_WIDTH = 320;
        const uint DESIGNED_RESOLUTION_HEIGHT = 200;
        const float DESIGNED_RESOLUTION_ASPECT_RATIO = static_cast<float>(DESIGNED_RESOLUTION_WIDTH) / static_cast<float>(DESIGNED_RESOLUTION_HEIGHT);
        
        sf::FloatRect getScaleRectangle() const;
        void windowResized();

        static Core* INSTANCE;
        
    public:
        static Core* Instance() { return INSTANCE; }
        
        Core();
        void run();
        void update(float delta);
        void draw();
        int getScale();
        sf::RenderWindow* getWindow();
    };
}
