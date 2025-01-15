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
        std::stack<std::unique_ptr<IScene>> sceneStack_;

    public:
        SceneManager();

        void addScene(std::unique_ptr<IScene> scene);
        void removeScene();
        void resetScene();
        IScene* getCurrentScene();
    };
}
