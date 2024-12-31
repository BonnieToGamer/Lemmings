//
// Created by filip on 2024-12-26.
//

#include "Entrance.h"

#include <stdexcept>

namespace Lemmings {
    float Entrance::calcSpawnRate() const
    {
        return 120.0f / static_cast<float>(this->spawnRate_);
    }

    Entrance::Entrance(GameUI* ui, sf::Vector2i position, LemmingsHandler* lemmingsHandler, uint spawnRate) : spawnTimer_(0.0f), ui_(std::move(ui)), position_(position), currentAnimationFrame_(0), lemmingsHandler_(lemmingsHandler), spawnRate_(spawnRate)
    {
        this->ui_->spawnRateChanged += [this](uint newSpawnRate) { this->spawnRateChanged(newSpawnRate); };
        this->spawnTimer_ = Engine::Timer(this->calcSpawnRate());
    }

    void Entrance::init()
    {
        const auto texture = std::make_shared<sf::Texture>();
        
        if (!texture->loadFromFile(ASSETS_PATH"entrance.png"))
            throw std::runtime_error("Couldn't load texture!");
        
        this->animatedTexture_ = std::make_unique<Engine::AnimatedTexture>(texture, sf::Vector2u(this->ENTRANCE_SPRITE_WIDTH, this->ENTRANCE_SPRITE_HEIGHT), true);
        this->animatedTexture_->addSpriteSheetAnim(10, 0, {0, 0}, 0);
        this->animatedTexture_->setPosition(this->position_.x, this->position_.y);
    }

    void Entrance::update(float delta)
    {
        if (this->currentAnimationFrame_ < NUMBER_OF_FRAMES && this->animationTimer_.update(delta))
        {
            this->animatedTexture_->nextFrame();
            this->currentAnimationFrame_++;
        }

        if (this->spawnTimer_.update(delta) && this->currentAnimationFrame_ >= NUMBER_OF_FRAMES)
        {
            this->lemmingsHandler_->addLemming(SPAWN_POINT + this->position_);
        }
    }

    void Entrance::draw(sf::RenderTarget& renderTarget)
    {
        this->animatedTexture_->draw(renderTarget);
    }

    void Entrance::spawnRateChanged(uint newSpawnRate)
    {
        this->spawnRate_ = newSpawnRate;
        this->spawnTimer_ = Engine::Timer(this->calcSpawnRate());
    }
} // Lemmings