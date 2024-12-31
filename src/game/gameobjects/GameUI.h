//
// Created by filip on 2024-12-25.
//

#pragma once
#include "Camera.h"
#include "../../engine/GameObject.h"
#include "./ui/ui_buttons/Button.h"
#include "./ui/ui_buttons/JobButton.h"
#include "../LevelData.h"
#include "ui/LemmingInfoDisplay.h"
#include "ui/TimeDisplay.h"

namespace Lemmings {

class GameUI final : public Engine::GameObject {
private:
    Camera* camera_;
    static constexpr uint AMOUNT_OF_BUTTONS = 13;
    std::vector<std::unique_ptr<UI::Button>> buttons_;
    UI::JobButton* currentJobButton_ = nullptr;
    LevelData* levelData_;
    uint mouseHoverAmount;
    Job mouseHoverJob;
    sf::Texture jobTextTexture_;
    sf::Sprite jobTextSprite_;
    UI::DualNumericSprite amountOfHoverdLemmings_;
    std::unique_ptr<UI::TimeDisplay> time_;
    std::unique_ptr<UI::LemmingInfoDisplay> lemmingStats_;

    const uint JOB_NAME_TEXTURE_WIDTH = 150;
    const uint JOB_NAME_TEXTURE_HEIGHT = 15;
    const sf::Vector2f timeUiPlacement = sf::Vector2f();

    template<typename ButtonType, typename... Args>
    void createButton(UI::UIButtonType id, Args&&... args);
public:
    Engine::Event<UI::UIButtonType> spawnRateChanged;
    
    explicit GameUI(Camera* cam, LevelData* levelData);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void cameraMoved();
    void buttonClicked(UI::UIButtonType index);
    void jobButtonClicked(UI::UIButtonType index);
    void releaseRateButtonClicked(UI::UIButtonType index);
    Job getCurrentJob();
    void decreaseCurrentJob();
    void setLemmingJobStat(uint amount, Job currentJob);
    bool canAssignCurrentJob();    
};
    
template<typename ButtonType, typename... Args>
void GameUI::createButton(UI::UIButtonType id, Args&&... args) {
    // perfect forwarding and compile-time conditional statements are nice.
    auto button = std::make_unique<ButtonType>(id, std::forward<Args>(args)...);
    
    if constexpr (std::is_same<ButtonType, UI::NumberButton>::value) {
        button->buttonClickEvent += [this](UI::UIButtonType index) {
            this->releaseRateButtonClicked(index);
        };
    } else if constexpr (std::is_same<ButtonType, UI::JobButton>::value) {
        button->buttonClickEvent += [this](UI::UIButtonType index) {
            this->jobButtonClicked(index);
        };
    } else {
        button->buttonClickEvent += [this](UI::UIButtonType index) {
            this->buttonClicked(index);
        };
    }

    this->buttons_.push_back(std::move(button));
}
} // Lemmings
