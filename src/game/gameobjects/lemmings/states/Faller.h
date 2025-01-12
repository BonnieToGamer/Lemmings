//
// Created by filip on 2024-12-16.
//

#pragma once
#include "../Lemming.h"
#include "../../../../engine/IState.h"

namespace Lemmings::States {

class Faller : public Engine::IState<Lemming> {
public:
    void enter() override;
    void exit() override;
    std::unique_ptr<IState<Lemming>> update(float delta) override;
};

} // Lemmings
