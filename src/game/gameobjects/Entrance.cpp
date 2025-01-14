//
// Created by filip on 2024-12-26.
//

#include "Entrance.h"

#include <stdexcept>

#include "../../engine/asset/ContentManager.h"

namespace Lemmings {
    Engine::Event<> Entrance::spawnEvent;
    
    float Entrance::calcSpawnRate() const
    {
        // A really rough interpretation of lemmings spawn rate system.
        // I counted frames between spawn rates 50 and 100 which equaled
        // 121 and 16 frames respectively on a 60 fps video
        return -0.035066f * static_cast<float>(this->spawnRate_ - 50) + 2.02;
    }

    Entrance::Entrance(sf::Vector2i position, LemmingsHandler* lemmingsHandler, uint spawnRate, uint amountOfLemmings) : spawnTimer_(nullptr), position_(position), currentAnimationFrame_(0), lemmingsHandler_(lemmingsHandler), spawnRate_(spawnRate), amountOfLemmings_(amountOfLemmings)
    {
        GameUI::spawnRateChangedEvent += this->SPAWN_RATE_CHANGED_HANDLER;
        this->spawnTimer_ = std::make_unique<Engine::Timer>(this->calcSpawnRate());
    }

    Entrance::~Entrance()
    {
        GameUI::spawnRateChangedEvent -= this->SPAWN_RATE_CHANGED_HANDLER;
    }

    void Entrance::init()
    {        
        this->texture_ = Engine::Core::contentManager->getTexture("entrance");
        this->spriteSheet_ = std::make_unique<Engine::SpriteSheet>(sf::Vector2u(this->ENTRANCE_SPRITE_WIDTH, this->ENTRANCE_SPRITE_HEIGHT), this->texture_);
        this->animation_ = std::make_unique<Engine::SpriteSheetAnimation>(this->spriteSheet_.get(), Engine::SpriteSheetAnimation::Right, NUMBER_OF_FRAMES + 1, sf::Vector2u(0, 0));

        this->spriteSheet_->init();
        this->spriteSheet_->setPosition(this->position_.x, this->position_.y);

        this->spawnTimer_->onTimerCompleteEvent += [this] { this->spawnTimerComplete(); };
        this->animationTimer_.onTimerCompleteEvent += [this] { this->animationTimerComplete(); };
    }

    void Entrance::update(float delta)
    {
        this->animationTimer_.update(delta);
        this->spawnTimer_->update(delta);
    }

    void Entrance::draw(sf::RenderTarget& renderTarget)
    {
        this->spriteSheet_->draw(renderTarget);
    }

    void Entrance::spawnRateChanged(uint newSpawnRate)
    {
        this->spawnRate_ = newSpawnRate;
        this->spawnTimer_->changeStopTime(this->calcSpawnRate());
    }

    void Entrance::spawnTimerComplete()
    {
        if (this->currentAnimationFrame_ < NUMBER_OF_FRAMES || this->currentAmountOfLemmings_ >= this->amountOfLemmings_)
            return;

        this->lemmingsHandler_->addLemming(SPAWN_POINT + this->position_);
        this->currentAmountOfLemmings_++;
        spawnEvent.invoke();
    }

    void Entrance::animationTimerComplete()
    {
        if (this->currentAnimationFrame_ >= NUMBER_OF_FRAMES)
            return;
        
        this->animation_->nextFrame();
        this->currentAnimationFrame_++;
    }

    uint Entrance::getAmountOut() const
    {
        return this->currentAmountOfLemmings_;
    }
} // Lemmings