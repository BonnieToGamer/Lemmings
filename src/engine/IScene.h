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
    std::vector<std::shared_ptr<GameObject>> gameObjects_;    

protected:
    void addGameObject(const std::shared_ptr<GameObject>& gameObject);
    
public:
    virtual ~IScene() = default;
    virtual void init();
    virtual void update(float delta);
    virtual void draw(sf::RenderTexture& renderTexture);
};

inline void IScene::addGameObject(const std::shared_ptr<GameObject>& gameObject)
{
    this->gameObjects_.emplace_back(gameObject);
}

inline void IScene::init()
{
    for (auto gameObject : this->gameObjects_)
        gameObject->init();
}

inline void IScene::update(float delta)
{
    for (auto gameObject : this->gameObjects_)
        gameObject->update(delta);
}

inline void IScene::draw(sf::RenderTexture& renderTexture)
{
    for (auto gameObject : this->gameObjects_)
        gameObject->draw(renderTexture);
}
} // Lemmings
