//
// Created by filip on 2024-12-26.
//

#include "Entrance.h"

#include <stdexcept>

namespace Lemmings {
    Engine::Event<uint> Entrance::spawnEvent;
    
    float Entrance::calcSpawnRate() const
    {
        // A really rough interpretation of lemmings spawn rate system.
        // I counted frames between spawn rates 50 and 100 which equaled
        // 121 and 16 frames respectively on a 60 fps video
        return -0.035066f * static_cast<float>(this->spawnRate_ - 50) + 2.02;
    }

    Entrance::Entrance(sf::Vector2i position, LemmingsHandler* lemmingsHandler, uint spawnRate, uint amountOfLemmings) : spawnTimer_(0.0f), position_(position), currentAnimationFrame_(0), lemmingsHandler_(lemmingsHandler), spawnRate_(spawnRate), amountOfLemmings_(amountOfLemmings)
    {
        GameUI::spawnRateChangedEvent += this->SPAWN_RATE_CHANGED_HANDLER;
        this->spawnTimer_ = Engine::Timer(this->calcSpawnRate());
    }

    Entrance::~Entrance()
    {
        GameUI::spawnRateChangedEvent -= this->SPAWN_RATE_CHANGED_HANDLER;
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

        if (this->spawnTimer_.update(delta) && this->currentAnimationFrame_ >= NUMBER_OF_FRAMES && this->currentAmountOfLemmings_ < this->amountOfLemmings_)
        {
            this->lemmingsHandler_->addLemming(SPAWN_POINT + this->position_);
            this->currentAmountOfLemmings_++;
            spawnEvent.invoke(this->currentAmountOfLemmings_);
        }
    }

    void Entrance::draw(sf::RenderTarget& renderTarget)
    {
        this->animatedTexture_->draw(renderTarget);
    }

    void Entrance::spawnRateChanged(uint newSpawnRate)
    {
        this->spawnRate_ = newSpawnRate;
        this->spawnTimer_.changeStopTime(this->calcSpawnRate());
    }
} // Lemmings