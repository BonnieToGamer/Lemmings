//
// Created by filip on 2024-12-26.
//

#pragma once
#include "GameUI.h"
#include "../../engine/AnimatedTexture.h"
#include "../../engine/GameObject.h"
#include "../../engine/Timer.h"
#include "lemmings/LemmingsHandler.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings {

class Entrance final : public Engine::GameObject {
private:
    std::unique_ptr<Engine::AnimatedTexture> animatedTexture_;
    Engine::Timer animationTimer_ = Engine::Timer(0.0667f);
    Engine::Timer spawnTimer_;
    uint spawnRate_ = 0;
    GameUI* ui_;
    sf::Vector2i position_;
    uint currentAnimationFrame_;
    LemmingsHandler* lemmingsHandler_;

    const sf::Vector2i SPAWN_POINT = { 21, 15 };
    const uint ENTRANCE_SPRITE_WIDTH = 41;
    const uint ENTRANCE_SPRITE_HEIGHT = 23;
    const uint NUMBER_OF_FRAMES = 9;

    float calcSpawnRate() const;
public:
    Entrance(GameUI* ui, sf::Vector2i position, LemmingsHandler* lemmingsHandler, uint spa);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void spawnRateChanged(uint newSpawnRate);
};

} // Lemmings
