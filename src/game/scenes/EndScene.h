//
// Created by filip on 2025-01-12.
//

#pragma once
#include "../../engine/IScene.h"
#include "SFML/Graphics/Text.hpp"

namespace Lemmings::Scene
{
class EndScene final : public Engine::IScene {
private:
    sf::Text text_;
    
public:
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void destroy() override;
};
}
