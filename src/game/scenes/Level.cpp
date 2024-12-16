//
// Created by filip on 2024-12-16.
//

#include "Level.h"

#include <iostream>

#include "../Map.h"
#include "../../engine/Core.h"
#include "../lemmings/Lemming.h"

namespace Lemmings::Scene {
    void Level::init()
    {
        const auto map = std::make_shared<Map>(ASSETS_PATH"map.png");
        const auto lemming = std::make_shared<Lemming>(map);
        lemming->setPosition(sf::Vector2f(3, 0));
        this->addGameObject(map);
        this->addGameObject(lemming);

        IScene::init();
    }

    void Level::update(float delta)
    {
        IScene::update(delta);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            Engine::Core::Instance()->getWindow()->close();
            return;
        }

        // sf::Vector2i mousePos =
        //     sf::Mouse::getPosition(*Engine::Core::Instance()->getWindow())
        //     / Engine::Core::Instance()->getScale()
        //     - sf::Vector2i(4, 4);
    }

    void Level::draw(sf::RenderTexture& renderTexture)
    {
        IScene::draw(renderTexture);
    }
} // Lemmings