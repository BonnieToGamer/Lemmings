//
// Created by filip on 2025-01-11.
//

#pragma once

#include "../Lemming.h"
#include "../../../../engine/IState.h"

namespace Lemmings::States {

class Builder final : public Engine::IState<Lemming> {
private:
    uint frameCounter = 0;
    uint placedTiles = 0;
    bool shrugState = false;

    const uint AMOUNT_OF_TILES = 12; // DOS version has 12. This depends on version. NES has 16 for example
    const sf::Color BUILD_BLOCK_COLOR = sf::Color(198, 185, 246);
    
public:
    void enter() override;
    void exit() override;
    std::unique_ptr<IState> update(float delta) override;
};

} // Lemmings
