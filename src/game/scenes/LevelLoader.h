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
    unsigned int currentLevelIndex = 1;

public:
    static Engine::Event<unsigned int> changeLevelEvent;
    
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void destroy() override;
};

} // Lemmings
