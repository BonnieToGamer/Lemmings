//
// Created by filip on 2025-01-12.
//

#pragma once
#include <sys/types.h>

#include "../../engine/Event.h"
#include "../../engine/IScene.h"

namespace Lemmings::Scene {

class LevelLoader final : public Engine::IScene{
private:
    uint currentLevelIndex = 4;

public:
    static Engine::Event<uint> changeLevelEvent;
    
    inline void init() override;
    inline void update(float delta) override;
    inline void draw(sf::RenderTarget& renderTarget) override;
    void destroy() override;
};

} // Lemmings
