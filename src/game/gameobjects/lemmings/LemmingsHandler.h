//
// Created by filip on 2024-12-23.
//

#pragma once
#include <vector>
#include "Lemming.h"
#include "../../../engine/Timer.h"

namespace Lemmings {

class LemmingsHandler final : public Engine::GameObject {
private:
    std::vector<std::unique_ptr<Lemming>> lemmings_;
    Engine::Timer fixedUpdateTimer_;
    Map* map_;

    void onLemmingDeath(Lemming* lemming);
    
public:
    explicit LemmingsHandler(Map* map);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;

    void addLemming(sf::Vector2i position);
    std::vector<Lemming*> checkCollision(sf::FloatRect rect);
};

} // Lemmings
