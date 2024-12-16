//
// Created by filip on 2024-12-16.
//

#include "Lemming.h"

#include <stdexcept>

#include "SFML/Graphics/RectangleShape.hpp"
#include "states/Walker.h"

namespace Lemmings {
    Lemming::Lemming(const std::shared_ptr<Map>& map) : map_(map) { }

    void Lemming::init()
    {
        this->stateMachineManager_ =
            std::make_unique<Engine::StateMachineManager<Lemming>>(std::make_shared<States::Walker>(), this->shared_from_this());


        auto walkerAnim = std::make_shared<Engine::AnimatedTexture>();
        auto fallerAnim = std::make_shared<Engine::AnimatedTexture>();
        const auto walk1 = std::make_shared<sf::Texture>();
        const auto walk2 = std::make_shared<sf::Texture>();
        const auto fall1 = std::make_shared<sf::Texture>();
        const auto fall2 = std::make_shared<sf::Texture>();
        
        if (!walk1->loadFromFile(ASSETS_PATH"lemming.png"))
            throw std::runtime_error("Couldn't load texture!");
        if (!walk2->loadFromFile(ASSETS_PATH"lemming1.png"))
            throw std::runtime_error("Couldn't load texture!");

        if (!fall1->loadFromFile(ASSETS_PATH"lemmingfall.png"))
            throw std::runtime_error("Couldn't load texture!");

        if (!fall2->loadFromFile(ASSETS_PATH"lemmingfall2.png"))
            throw std::runtime_error("Couldn't load texture!");
        
        walkerAnim->addToTimeline(0.0f, walk1);
        walkerAnim->addToTimeline(0.25f, walk2);
        walkerAnim->addToTimeline(0.5f, walk2);

        fallerAnim->addToTimeline(0.0f, fall1);
        fallerAnim->addToTimeline(0.25f, fall2);
        fallerAnim->addToTimeline(0.5f, fall2);

        this->animations_.emplace("Walker", walkerAnim);
        this->animations_.emplace("Faller", fallerAnim);

        this->currentAnimatedTexture_ = walkerAnim;
    }

    void Lemming::update(float delta)
    {
        this->currentAnimatedTexture_->update(delta);
        if (this->fixedUpdateTimer_.update(delta))
            this->stateMachineManager_->update(delta);
    }

    void Lemming::draw(sf::RenderTexture& renderTexture)
    {
        this->currentAnimatedTexture_->setPosition(this->position_.x - TEXTURE_WIDTH / 2, this->position_.y - TEXTURE_HEIGHT + 1);
        this->currentAnimatedTexture_->draw(renderTexture);
    }

    const sf::Vector2f& Lemming::getPosition()
    {
        return this->position_;
    }

    void Lemming::setPosition(const sf::Vector2f& newPos)
    {
        this->position_ = newPos;
    }

    const std::shared_ptr<Map>& Lemming::map()
    {
        return this->map_;
    }

    void Lemming::playAnimation(const std::string& name)
    {
        if (auto itr = this->animations_.find(name); itr == this->animations_.end())
            return;
            
        this->currentAnimatedTexture_ = this->animations_[name];
        this->currentAnimatedTexture_->init();
    }
} // Lemmings