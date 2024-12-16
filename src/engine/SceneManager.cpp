//
// Created by filip on 2024-12-16.
//

#include "SceneManager.h"

namespace Lemmings::Engine
{
    SceneManager::SceneManager() : sceneStack_() { }

    void SceneManager::addScene(const std::shared_ptr<IScene>& scene)
    {
        scene->init();
        this->sceneStack_.push(scene);
    }

    void SceneManager::removeScene()
    {
        if (this->sceneStack_.empty())
            return;
        
        this->sceneStack_.pop();
    }

    std::shared_ptr<IScene> SceneManager::getCurrentScene()
    {
        if (this->sceneStack_.empty())
            return nullptr;
        
        return this->sceneStack_.top();
    }
}