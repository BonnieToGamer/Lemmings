//
// Created by filip on 2025-01-12.
//

#pragma once
#include "../../engine/IScene.h"
#include "SFML/Graphics/Text.hpp"

namespace Lemmings::Scene
{
class EndScene : public Engine::IScene {
private:
    sf::Text text_;
    
public:
    inline void init() override;
    inline void update(float delta) override;
    inline void draw(sf::RenderTarget& renderTarget) override;
    void destroy() override;
};
}
