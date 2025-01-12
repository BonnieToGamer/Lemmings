//
// Created by filip on 2025-01-11.
//

#pragma once

#include "../Lemming.h"
#include "../../../../engine/IState.h"

namespace Lemmings::States {

class Blocker final : public Engine::IState<Lemming> {
private:
    std::vector<sf::Vector2i> placed_;
    
public:
    void enter() override;
    void exit() override;
    std::unique_ptr<IState> update(float delta) override;

};

} // Lemmings
