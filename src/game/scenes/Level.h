//
// Created by filip on 2024-12-16.
//

#pragma once
#include "../../engine/IScene.h"
#include "../../engine/ModifiableTexture.h"
#include "SFML/Graphics/Text.hpp"

namespace Lemmings::Scene {

class Level : public Engine::IScene {
public:
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
};

} // Lemmings
