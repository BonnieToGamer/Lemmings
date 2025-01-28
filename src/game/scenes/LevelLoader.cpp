//
// Created by filip on 2025-01-12.
//

#include "LevelLoader.h"

namespace Lemmings::Scene {
    Engine::Event<unsigned int> LevelLoader::changeLevelEvent;
    
    void LevelLoader::init()
    {
        IScene::init();
    }

    void LevelLoader::update(float delta)
    {
        IScene::update(delta);
        changeLevelEvent.invoke(this->currentLevelIndex++);
    }

    void LevelLoader::draw(sf::RenderTarget& renderTarget)
    {
        IScene::draw(renderTarget);
    }
    
    void LevelLoader::destroy()
    {
    }
} // Lemmings