//
// Created by filip on 2025-01-12.
//

#pragma once
#include "Faller.h"
#include "Walker.h"

namespace Lemmings::States
{
class Floater final : public  Engine::IState<Lemming> {
private:
    enum FloaterStates
    {
        Walk,
        Fall,
        ParachuteOpen,
        ParachuteGlide
    };

    FloaterStates state_;
    Walker walker_;
    Faller faller_;
    unsigned int fallFrames_ = 0;
    unsigned int frameCounter_ = 0;

    const unsigned int MAX_FALL_FRAMES_UNTIL_PARACHUTE = 6;
    
public:
    void enter() override;
    void exit() override;
    void walkUpdate(float delta);
    void fallUpdate(float delta);
    void parachuteOpenUpdate(float delta);
    void parachuteGlideUpdate(float delta);
    void fallAndCollide();
    std::unique_ptr<IState<Lemming>> update(float delta) override;
};
}