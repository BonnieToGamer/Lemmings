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
    LevelData* data_;
    std::queue<Lemming*> removalQueue_;

    void onLemmingDeath(Lemming* lemming);
    void onLemmingWin(Lemming* lemming);
    void processRemovalQueue();
    
    const std::function<void(Lemming*)> LEMMING_DEATH_HANDLER = [this] (Lemming* lemming) { this->onLemmingDeath(lemming); };
    const std::function<void(Lemming*)> LEMMING_WIN_HANDLER = [this] (Lemming* lemming) { this->onLemmingWin(lemming); };
    
public:
    static Engine::Event<> lemmingWinEvent;
    
    explicit LemmingsHandler(Map* map, LevelData* data);
    ~LemmingsHandler() override;
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;

    void addLemming(sf::Vector2i position);
    std::vector<Lemming*> checkCollision(sf::FloatRect rect);
    uint getAmountOfLemmings();
};

} // Lemmings
