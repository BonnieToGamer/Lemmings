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
    unsigned int nukeIndex_ = 0;
    bool nukeStarted_ = false;
    bool paused_ = false;
    unsigned int amountWon = 0;

    void onLemmingDeath(Lemming* lemming);
    void onLemmingWin(Lemming* lemming);
    void processRemovalQueue();
    void pause();
    void nuke();
    
    const std::function<void(Lemming*)> LEMMING_DEATH_HANDLER = [this] (Lemming* lemming) { this->onLemmingDeath(lemming); };
    const std::function<void(Lemming*)> LEMMING_WIN_HANDLER = [this] (Lemming* lemming) { this->onLemmingWin(lemming); };
    const std::function<void()> NUKE_HANDLER = [this]{ this->nuke(); };
    const std::function<void()> PAUSE_HANDLER = [this] { this->pause(); };
    
public:
    static Engine::Event<> lemmingWinEvent;
    
    explicit LemmingsHandler(Map* map, LevelData* data);
    ~LemmingsHandler() override;
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;

    void addLemming(sf::Vector2i position);
    std::vector<Lemming*> checkCollision(sf::FloatRect rect) const;
    unsigned int getAmountWon() const;
    unsigned int getAmountOfLemmings() const;
};

} // Lemmings
