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
    static constexpr unsigned int AMOUNT_OF_BUTTONS = 13;
    std::vector<UI::Button*> buttons_;
    UI::JobButton* currentJobButton_ = nullptr;
    const LevelData* levelData_;
    unsigned int mouseHoverAmount;
    unsigned int currentReleaseRate_;
    Job mouseHoverJob;
    sf::Texture* jobTextTexture_;
    sf::Sprite jobTextSprite_;
    UI::DualNumericSprite* amountOfHoveredLemmings_;
    UI::TimeDisplay* time_;
    UI::LemmingInfoDisplay* lemmingStats_;
    
    unsigned int amountOut = 0;
    unsigned int amountIn = 0;

    const unsigned int JOB_NAME_TEXTURE_WIDTH = 55;
    const unsigned int JOB_NAME_TEXTURE_HEIGHT = 15;
    const std::function<void()> SPAWN_EVENT_HANDLER = [this] { this->setAmountOut(); };
    const std::function<void()> LEMMING_WIN_HANDLER = [this]  { this->updateAmountIn(); };
    const std::function<void(Camera*)> CAMERA_MOVED_HANDLER = [this] (Camera* sender) { this->cameraMoved(sender); };

    template<typename ButtonType, typename... Args>
    void createButton(UI::UIButtonType id, Args&&... args);
public:
    static Engine::Event<unsigned int> spawnRateChangedEvent;
    static Engine::Event<> nukeEvent;
    static Engine::Event<> pauseEvent;
    
    explicit GameUI(const LevelData* levelData);
    ~GameUI() override;
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void cameraMoved(const Camera* camera);
    void buttonClicked(UI::UIButtonType index) const;
    void jobButtonClicked(UI::UIButtonType index);
    void releaseRateButtonClicked(UI::UIButtonType index);
    Job getCurrentJob() const;
    void decreaseCurrentJob() const;
    void setLemmingJobStat(unsigned int amount, Job currentJob);
    bool canAssignCurrentJob() const;
    void setAmountOut();
    void updateAmountIn();
};
    
template<typename ButtonType, typename... Args>
void GameUI::createButton(UI::UIButtonType id, Args&&... args) {
    // perfect forwarding and compile-time conditional statements are nice.
    // although I miss my reflections
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

    this->buttons_.push_back(button.get());
    this->addChild(std::move(button));
}
} // Lemmings
