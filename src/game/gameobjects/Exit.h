//
// Created by filip on 2024-12-26.
//

#pragma once
#include "../LevelData.h"
#include "../../engine/SpriteSheet.h"
#include "../../engine/SpriteSheetAnimation.h"
#include "../../engine/Timer.h"

namespace Lemmings {

class Exit final : public Engine::GameObject {
private:
    LevelData* data_;
    sf::Texture* texture_ = nullptr;
    std::unique_ptr<Engine::SpriteSheetAnimation> animation_;

    Engine::Timer animationTimer_ = Engine::Timer(0.0667f);

    static constexpr uint TEXTURE_WIDTH = 44;
    static constexpr uint TEXTURE_HEIGHT = 52;

    void animationTimerFinished() const;
    
public:
    static constexpr uint COLLIDER_WIDTH = 7;
    static constexpr uint COLLIDER_HEIGHT = -TEXTURE_HEIGHT;
    static sf::IntRect collisionArea;

    explicit Exit(LevelData* data);
    ~Exit() override;
    
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
};

} // Lemmings
