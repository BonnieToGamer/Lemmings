//
// Created by filip on 2024-12-26.
//

#include "Exit.h"

#include "../../engine/Core.h"

namespace Lemmings {
    sf::IntRect Exit::collisionArea;
    
    void Exit::animationTimerFinished()
    {
        this->animation_->nextFrame();
    }

    Exit::Exit(LevelData* data) : data_(data)
    {
    }

    Exit::~Exit()
    {
        collisionArea = sf::IntRect(0, 0, 0,0);
    }

    void Exit::init()
    {
        this->texture_ = Engine::Core::contentManager->getTexture("exit");
        auto spriteSheet = std::make_unique<Engine::SpriteSheet>(sf::Vector2u(TEXTURE_WIDTH, TEXTURE_HEIGHT), this->texture_);
        this->animation_ = std::make_unique<Engine::SpriteSheetAnimation>(spriteSheet.get(), Engine::SpriteSheetAnimation::Right, 6, sf::Vector2u(0, 0));
        spriteSheet->setPosition(this->data_->exitX, this->data_->exitY);

        this->addChild(std::move(spriteSheet));
        GameObject::init();

        this->animationTimer_.onTimerCompleteEvent += [this] { this->animationTimerFinished(); };
        collisionArea = sf::IntRect(this->data_->exitX + 18, this->data_->exitY +  44, 8, 8);
    }

    void Exit::update(float delta)
    {
        this->animationTimer_.update(delta);
        GameObject::update(delta);
    }

    void Exit::draw(sf::RenderTarget& renderTarget)
    {
        GameObject::draw(renderTarget);
        // sf::RectangleShape rect({8, 8});
        // rect.setPosition(this->data_->exitX + 18, this->data_->exitY + 44);
        // rect.setFillColor(sf::Color::Green);
        // renderTarget.draw(rect);
        //
        // sf::RectangleShape rect2({1, 1});
        // rect2.setPosition(this->data_->exitX, this->data_->exitY);
        // rect2.setFillColor(sf::Color::Green);
        // renderTarget.draw(rect2);
    }
} // Lemmings