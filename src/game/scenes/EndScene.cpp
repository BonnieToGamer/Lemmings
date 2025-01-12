//
// Created by filip on 2025-01-12.
//

#include "EndScene.h"

#include "../../engine/Core.h"
#include "../../engine/asset/ContentManager.h"
#include "../gameobjects/Camera.h"

void Lemmings::Scene::EndScene::init()
{
    this->text_.setFont(*Engine::Core::contentManager->getFont("Roboto"));
    this->text_.setString("Wow, you got to the end...");
    this->text_.setCharacterSize(12);
    this->text_.setFillColor(sf::Color::White);
    this->text_.setPosition(100, 0);
    
    IScene::init();
}

void Lemmings::Scene::EndScene::update(float delta)
{
    IScene::update(delta);
}

void Lemmings::Scene::EndScene::draw(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(this->text_);
    IScene::draw(renderTarget);
}

void Lemmings::Scene::EndScene::destroy()
{
}
