//
// Created by filip on 2024-12-26.
//

#pragma once
#include "GameUI.h"
#include "../../engine/GameObject.h"
#include "../../engine/Timer.h"
#include "lemmings/LemmingsHandler.h"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings {

class Entrance final : public Engine::GameObject {
private:
    sf::Texture* texture_ = nullptr;
    std::unique_ptr<Engine::SpriteSheet> spriteSheet_;
    std::unique_ptr<Engine::SpriteSheetAnimation> animation_;
    
    Engine::Timer animationTimer_ = Engine::Timer(0.0667f);
    std::unique_ptr<Engine::Timer> spawnTimer_;
    sf::Vector2i position_;
    LemmingsHandler* lemmingsHandler_;
    uint currentAnimationFrame_;
    uint spawnRate_ = 0;
    uint amountOfLemmings_;
    uint currentAmountOfLemmings_ = 0;

    const sf::Vector2i SPAWN_POINT = { 21, 15 };
    const uint ENTRANCE_SPRITE_WIDTH = 41;
    const uint ENTRANCE_SPRITE_HEIGHT = 23;
    const uint NUMBER_OF_FRAMES = 9;
    const std::function<void(uint)> SPAWN_RATE_CHANGED_HANDLER = [this](uint newSpawnRate) { this->spawnRateChanged(newSpawnRate); };

    float calcSpawnRate() const;
public:
    static Engine::Event<> spawnEvent;
    
    Entrance(sf::Vector2i position, LemmingsHandler* lemmingsHandler, uint spawnRate, uint amountOfLemmings);
    ~Entrance();
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void spawnRateChanged(uint newSpawnRate);
    void spawnTimerComplete();
    void animationTimerComplete();
    uint getAmountOut();
};

} // Lemmings
