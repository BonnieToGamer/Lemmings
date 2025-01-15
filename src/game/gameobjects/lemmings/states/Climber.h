//
// Created by filip on 2025-01-15.
//

#pragma once

#include "Faller.h"
#include "Walker.h"
#include "../Lemming.h"
#include "../../../../engine/IState.h"

namespace Lemmings::States
{
class Climber final : public Engine::IState<Lemming> {
private:
    enum ClimberState
    {
        Walk,
        Fall,
        Climb,
        Vault
    };

    ClimberState state_;
    Walker walker_;
    Faller faller_;
    uint frameCounter_ = 0;

public:
    void walkUpdate(float delta);
    void fallUpdate(float delta);
    void climbUpdate(float delta);
    void vaultUpdate(float delta);
    
    void enter() override;
    void exit() override;
    std::unique_ptr<IState> update(float delta) override;
};
}