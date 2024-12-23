//
// Created by filip on 2024-12-24.
//

#pragma once
#include "../Lemming.h"
#include "../../../engine/IState.h"

namespace Lemmings::States
{
class Digger final : public Engine::IState<Lemming> {
private:
    int digCounter_ = 0;
        
public:
    void enter() override;
    void exit() override;
    std::shared_ptr<IState> digDown();
    std::shared_ptr<IState> update(float delta) override;
};
}// Lemmings
