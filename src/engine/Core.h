//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>

#include "Event.h"
#include "SceneManager.h"
#include "Timer.h"
#include "asset/ContentManager.h"
#include "SFML/Graphics.hpp"

namespace Lemmings::Engine
{
    class Core {
    private:
        std::unique_ptr<sf::RenderWindow> renderWindow_;
        SceneManager sceneManager_;
        sf::RenderTexture renderTexture_;
        sf::Sprite renderSprite_;
        const float DESIGNED_RESOLUTION_ASPECT_RATIO = static_cast<float>(DESIGNED_RESOLUTION_WIDTH) / static_cast<float>(DESIGNED_RESOLUTION_HEIGHT);
        Timer slowTimer_ = Timer(0.30f);
        std::unordered_map<unsigned int, std::string> levels_;

        static Core* INSTANCE;
        const std::function<void(unsigned int)> CHANGE_LEVEL_EVENT = [this](unsigned int levelIndex) { this->loadNewLevel(levelIndex); };

        void loadNewLevel(unsigned int levelIndex);
        void loadLevelIndices();
        
    public:
        static constexpr unsigned int DESIGNED_RESOLUTION_WIDTH = 320;
        static constexpr unsigned int DESIGNED_RESOLUTION_HEIGHT = 200;
        static Event<> windowSizeChangedEvent;
        static std::unique_ptr<Asset::ContentManager> contentManager;
        
        static Core* Instance() { return INSTANCE; }
        
        Core();
        ~Core();
        void run();
        void update(float delta);
        void draw();
        void removeCurrentScene();
        void resetCurrentScene();
        sf::RenderWindow* getWindow() const;
    };
}
