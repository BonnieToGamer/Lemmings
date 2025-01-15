//
// Created by filip on 2024-12-16.
//

#pragma once
#include <memory>

#include "GameObject.h"
#include "SFML/Graphics/RenderTexture.hpp"

namespace Lemmings::Engine {

class IScene
{
private:
    std::vector<std::unique_ptr<GameObject>> gameObjects_;    

protected:
    void addGameObject(std::unique_ptr<GameObject> gameObject);
    
public:
    virtual ~IScene() = default;
    virtual void init();
    virtual void destroy();
    virtual void update(float delta);
    virtual void draw(sf::RenderTarget& renderTarget);
};

inline void IScene::addGameObject(std::unique_ptr<GameObject> gameObject)
{
    this->gameObjects_.emplace_back(std::move(gameObject));
}

inline void IScene::init()
{
    for (const auto& gameObject : this->gameObjects_)
        gameObject->init();
}

inline void IScene::destroy()
{
    gameObjects_.clear();
}

inline void IScene::update(float delta)
{
    for (const auto& gameObject : this->gameObjects_)
        gameObject->update(delta);
}

inline void IScene::draw(sf::RenderTarget& renderTarget)
{
    for (const auto& gameObject : this->gameObjects_)
        gameObject->draw(renderTarget);
}
} // Lemmings
