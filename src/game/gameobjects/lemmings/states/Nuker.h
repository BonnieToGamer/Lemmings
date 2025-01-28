//
// Created by filip on 2025-01-15.
//

#pragma once

#include "../Lemming.h"
#include "../../../../engine/IState.h"

namespace Lemmings::States {

class Nuker  final : public Engine::IState<Lemming> {
private:
    Job prevJob_;
    unsigned int animationIndex_ = 0;
    bool exploded = false;
    
public:
    explicit Nuker(Job previousJob);
    void explode();
    void enter() override;
    void exit() override;
    std::unique_ptr<IState<Lemming>> update(float delta) override;
};

} // Lemmings
