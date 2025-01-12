//
// Created by filip on 2024-12-16.
//

#pragma once
#include "../LevelData.h"
#include "../../engine/IScene.h"
#include "../../engine/ModifiableTexture.h"
#include "../gameobjects/Entrance.h"

namespace Lemmings::Scene {

class Level : public Engine::IScene {
private:
    std::string levelName_;
    std::unique_ptr<LevelData> levelData_;
    Entrance* entrance_ = nullptr;
    LemmingsHandler* lemmingHandler_ = nullptr;
    
public:
    Level(const std::string& levelName);
    std::unique_ptr<LevelData> parseLevel() const;
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void destroy() override;
};

} // Lemmings
