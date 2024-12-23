//
// Created by filip on 2024-12-16.
//

#include "Level.h"

#include <iostream>

#include "../Camera.h"
#include "../Map.h"
#include "../../engine/Core.h"
#include "../lemmings/Lemming.h"
#include "../lemmings/LemmingsHandler.h"

namespace Lemmings::Scene {
    void Level::init()
    {
        const auto map = std::make_shared<Map>(ASSETS_PATH"map2.png");
        const auto lemmingHandler = std::make_shared<LemmingsHandler>(map);
        const auto camera = std::make_shared<Camera>();
        
        lemmingHandler->addLemming({225, 29});
        
        this->addGameObject(camera);
        this->addGameObject(map);
        this->addGameObject(lemmingHandler);

        IScene::init();
        
        camera->activate();
        camera->setPosition({69, 0});
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

    void Level::draw(sf::RenderTarget& renderTarget)
    {
        IScene::draw(renderTarget);
    }
} // Lemmings