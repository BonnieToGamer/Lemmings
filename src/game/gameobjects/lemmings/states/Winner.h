//
// Created by filip on 2025-01-11.
//

#pragma once
#include "../Lemming.h"
#include "../../../../engine/IState.h"

namespace Lemmings::States {

class Winner final : public Engine::IState<Lemming> {
private:
    uint frameCounter = 0;
    
public:
    void enter() override;
    void exit() override;
    std::unique_ptr<IState<Lemming>> update(float delta) override;
};

} // Lemmings
