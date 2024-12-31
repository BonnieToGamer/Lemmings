//
// Created by filip on 2024-12-16.
//

#include "SceneManager.h"

namespace Lemmings::Engine
{
    SceneManager::SceneManager() : sceneStack_() { }

    void SceneManager::addScene(std::shared_ptr<IScene> scene)
    {
        scene->init();
        this->sceneStack_.push(std::move(scene));
    }

    void SceneManager::removeScene()
    {
        if (this->sceneStack_.empty())
            return;

        this->sceneStack_.top()->destroy();
        this->sceneStack_.pop();
    }

    std::shared_ptr<IScene> SceneManager::getCurrentScene()
    {
        if (this->sceneStack_.empty())
            return nullptr;
        
        return this->sceneStack_.top();
    }
}