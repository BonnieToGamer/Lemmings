//
// Created by filip on 2024-12-28.
//

#pragma once

#include "../Lemming.h"
#include "../../../../engine/IState.h"

namespace Lemmings::States {

class Miner final : public Engine::IState<Lemming> {
private:
    uint mineCounter = 0;

    void digStepOne(const sf::Vector2i& pos, Direction direction);
    bool shouldSkipFirstStep(int y, int x);
    bool digStepTwo(const sf::Vector2i& pos, Direction direction);
    bool shouldSkipSecondStep(int y, int x);
    void resetMineCounter(const sf::Vector2i& pos);

    static constexpr int DIG_STEP_ONE_WIDTH = 5;
    static constexpr int DIG_STEP_ONE_HEIGHT = 5;
    static constexpr int DIG_STEP_ONE_START_OFFSET_X_LEFT = -4;
    static constexpr int DIG_STEP_ONE_START_OFFSET_X_RIGHT = 3;
    static constexpr int DIG_STEP_ONE_START_OFFSET_Y = -11;

    static constexpr int DIG_STEP_TWO_WIDTH = 11;
    static constexpr int DIG_STEP_TWO_HEIGHT = 12;
    static constexpr int DIG_STEP_TWO_START_OFFSET_X_LEFT = 2;
    static constexpr int DIG_STEP_TWO_START_OFFSET_X_RIGHT = -1;
    static constexpr int DIG_STEP_TWO_START_OFFSET_Y = -9;

    static constexpr int MINE_COUNTER_STEP_ONE = 1;
    static constexpr int MINE_COUNTER_STEP_TWO = 2;
    static constexpr int MINE_COUNTER_RESET_THRESHOLD = 25;

    static constexpr int MINE_COUNTER_RESET_OFFSET_X_LEFT = -4;
    static constexpr int MINE_COUNTER_RESET_OFFSET_X_RIGHT = 4;
    static constexpr int MINE_COUNTER_RESET_OFFSET_Y = 2;

    static constexpr int ANIMATION_OFFSET_X_LEFT = -3;
    static constexpr int ANIMATION_OFFSET_X_RIGHT = 3;
    static constexpr int ANIMATION_OFFSET_Y = 4;



public:
    void enter() override;
    void exit() override;
    std::unique_ptr<IState<Lemming>> update(float delta) override;
};

} // Lemmings
