//
// Created by filip on 2024-12-26.
//

#pragma once
#include "NumberButton.h"
#include "../../lemmings/Lemming.h"

namespace Lemmings::UI {

class JobButton final : public NumberButton {
private:
    Job job_ = Job::Nothing;
    bool selected_;
    
public:
    JobButton(UI::UIButtonType buttonIndex, uint amount, bool held, Job job, float heldTimer = 0.0f, sf::Keyboard::Key shortCutKey = IGNORE_KEY);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void setPosition(sf::Vector2f pos) override;
    void setSelected(bool selected);
    Job getJob() const;
    void decreaseAmount();
};
} // Lemmings
