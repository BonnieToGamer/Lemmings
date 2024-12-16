//
// Created by filip on 2024-12-16.
//

#pragma once
#include "../Lemming.h"
#include "../../../engine/IState.h"

namespace Lemmings::States {

class Walker final : public Engine::IState<Lemming> {
private:
    int dir = 1;
    const float SPEED = 2;
    
public:
    void enter() override;
    void exit() override;
    std::shared_ptr<IState<Lemming>> update(float delta) override;
};

} // Lemmings
