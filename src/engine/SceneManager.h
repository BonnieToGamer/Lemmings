//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>
#include <stack>

#include "IScene.h"


namespace Lemmings::Engine
{
    class SceneManager {
    private:
        std::stack<std::shared_ptr<IScene>> sceneStack_;

    public:
        SceneManager();

        void addScene(std::shared_ptr<IScene> scene);
        void removeScene();
        std::shared_ptr<IScene> getCurrentScene();
    };
}
