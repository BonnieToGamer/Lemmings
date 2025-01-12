//
// Created by filip on 2024-12-25.
//

#include "GameUI.h"

#include <iostream>
#include <stdexcept>

#include "Entrance.h"
#include "../../engine/Core.h"

namespace Lemmings {
    Engine::Event<uint> GameUI::spawnRateChangedEvent;
    
    GameUI::GameUI(LevelData* levelData) : levelData_(levelData)
    {
    }

    GameUI::~GameUI()
    {
        Camera::movedEvent -= this->CAMERA_MOVED_HANDLER;
        Entrance::spawnEvent -= this->SPAWN_EVENT_HANDLER;
        LemmingsHandler::lemmingWinEvent -= this->LEMMING_WIN_HANDLER;
    }

    void GameUI::init()
    {
        Camera::movedEvent += this->CAMERA_MOVED_HANDLER;
        this->buttons_.reserve(this->AMOUNT_OF_BUTTONS);

        this->jobTextTexture_ = Engine::Core::contentManager->getTexture("job_names");

        float textY = Engine::Core::DESIGNED_RESOLUTION_HEIGHT - UI::Button::BUTTON_HEIGHT - JOB_NAME_TEXTURE_HEIGHT - 2.0f;

        this->jobTextSprite_.setTexture(*this->jobTextTexture_);
        this->jobTextSprite_.setPosition(0, textY);

        float heldTimer = 0.1f;

        createButton<UI::NumberButton>(UI::ReleaseRateDecrease, this->levelData_->releaseRate, true, heldTimer, sf::Keyboard::F1);
        createButton<UI::NumberButton>(UI::ReleaseRateIncrease, this->levelData_->releaseRate, true, heldTimer, sf::Keyboard::F2);
        createButton<UI::JobButton>(UI::Climber, this->levelData_->climbers, false, Job::Climber, 0.0f, sf::Keyboard::F3);
        createButton<UI::JobButton>(UI::Floater, this->levelData_->floaters, false, Job::Floater, 0.0f, sf::Keyboard::F4);
        createButton<UI::JobButton>(UI::Bomber, this->levelData_->bombers, false, Job::Bomber, 0.0f, sf::Keyboard::F5);
        createButton<UI::JobButton>(UI::Blocker, this->levelData_->blockers, false, Job::Blocker, 0.0f, sf::Keyboard::F6);
        createButton<UI::JobButton>(UI::Builder, this->levelData_->builders, false, Job::Builder, 0.0f, sf::Keyboard::F7);
        createButton<UI::JobButton>(UI::Basher, this->levelData_->bashers, false, Job::Basher, 0.0f, sf::Keyboard::F8);
        createButton<UI::JobButton>(UI::Miner, this->levelData_->miners, false, Job::Miner, 0.0f, sf::Keyboard::F9);
        createButton<UI::JobButton>(UI::Digger, this->levelData_->diggers, false, Job::Digger, 0.0f, sf::Keyboard::F10);
        createButton<UI::Button>(UI::Pause, false, 0.0f, sf::Keyboard::F11); // pause
        createButton<UI::Button>(UI::Nuke, false, 0.0f, sf::Keyboard::F12); // explode

        auto time = std::make_unique<UI::TimeDisplay>(sf::Vector2f(0, textY), this->levelData_->timeLimit);
        this->time_ = time.get();
        this->addChild(std::move(time));

        auto lemmingStats = std::make_unique<UI::LemmingInfoDisplay>(this->levelData_->amountOfLemmings);
        lemmingStats->init();
        lemmingStats->setPosition({0, textY});

        this->lemmingStats_ = lemmingStats.get();
        this->addChild(std::move(lemmingStats));
        
        auto hoveredLemmings = std::make_unique<UI::DualNumericSprite>();
        hoveredLemmings->init();
        hoveredLemmings->setPosition({0, textY});

        this->amountOfHoveredLemmings_ = hoveredLemmings.get();
        this->addChild(std::move(hoveredLemmings));

        this->currentReleaseRate_ = this->levelData_->releaseRate;

        Entrance::spawnEvent += this->SPAWN_EVENT_HANDLER;
        LemmingsHandler::lemmingWinEvent += this->LEMMING_WIN_HANDLER;
        GameObject::init();
    }

    void GameUI::update(float delta)
    {
        // this->time_->update(delta);
        // this->lemmingStats_->update(delta);
        GameObject::update(delta);
    }

    void GameUI::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->jobTextSprite_);
        // this->time_->draw(renderTarget);
        // this->lemmingStats_->draw(renderTarget);
        // this->amountOfHoveredLemmings_->draw(renderTarget);
        GameObject::draw(renderTarget);
    }

    void GameUI::cameraMoved(Camera* camera)
    {
        this->jobTextSprite_.setPosition(camera->position().x, this->jobTextSprite_.getPosition().y);
        this->time_->setPosition(sf::Vector2f(camera->position().x + Engine::Core::DESIGNED_RESOLUTION_WIDTH - UI::TimeDisplay::WIDTH, this->time_->getPosition().y));
        this->lemmingStats_->setPosition(sf::Vector2f(camera->position().x + 111, this->lemmingStats_->getPosition().y));
        this->amountOfHoveredLemmings_->setPosition(sf::Vector2f(camera->position().x + UI::NumericSprite::NUMBER_WIDTH * 9, this->amountOfHoveredLemmings_->getPosition().y));

        for (auto& button : this->buttons_)
            button->setPosition({camera->position().x + button->getIndex() * button->BUTTON_WIDTH, static_cast<float>(Engine::Core::DESIGNED_RESOLUTION_HEIGHT - button->BUTTON_HEIGHT)});
    }

    void GameUI::buttonClicked(UI::UIButtonType index)
    {
        std::cout << index << " clicked!" << std::endl;
    }

    void GameUI::jobButtonClicked(UI::UIButtonType index)
    {
        if (this->currentJobButton_ != nullptr)
            this->currentJobButton_->setSelected(false);
        
        std::cout << index << " job clicked!" << std::endl;
        this->currentJobButton_ = dynamic_cast<UI::JobButton*>(this->buttons_[index]);
        this->currentJobButton_->setSelected(true);
    }

    void GameUI::releaseRateButtonClicked(UI::UIButtonType index)
    {
       if (index == UI::ReleaseRateDecrease)
       {
           if (this->currentReleaseRate_ <= this->levelData_->releaseRate)
               return;

           this->currentReleaseRate_--;
           this->spawnRateChangedEvent.invoke(this->currentReleaseRate_);
           dynamic_cast<UI::NumberButton*>(this->buttons_[UI::ReleaseRateIncrease])->setAmount(this->currentReleaseRate_);
       }

        else if (index == UI::ReleaseRateIncrease)
        {
            if (this->currentReleaseRate_ >= 99)
                return;

            this->currentReleaseRate_++;
            this->spawnRateChangedEvent.invoke(this->currentReleaseRate_);
            dynamic_cast<UI::NumberButton*>(this->buttons_[UI::ReleaseRateIncrease])->setAmount(this->currentReleaseRate_);

        }
    }

    Job GameUI::getCurrentJob()
    {
        if (this->currentJobButton_ == nullptr) return Job::Nothing;
        return this->currentJobButton_->getJob();
    }

    void GameUI::decreaseCurrentJob()
    {
        this->currentJobButton_->decreaseAmount();
    }

    void GameUI::setLemmingJobStat(uint amount, Job currentJob)
    {
        this->mouseHoverAmount = amount;
        this->mouseHoverJob = currentJob;

        this->jobTextSprite_.setTextureRect({0, static_cast<int>(static_cast<int>(this->mouseHoverJob) * JOB_NAME_TEXTURE_HEIGHT), static_cast<int>(JOB_NAME_TEXTURE_WIDTH), static_cast<int>(JOB_NAME_TEXTURE_HEIGHT)});
        
        if (this->mouseHoverAmount != 0)
            this->amountOfHoveredLemmings_->setValue(this->mouseHoverAmount);
        else
            this->amountOfHoveredLemmings_->setEmpty();
    }

    bool GameUI::canAssignCurrentJob()
    {
        return this->currentJobButton_->getAmount() > 0;
    }

    void GameUI::setAmountOut()
    {
        this->lemmingStats_->setAmountOut(++this->amountOut);
    }

    void GameUI::updateAmountIn()
    {
        this->lemmingStats_->setAmountIn(++this->amountIn);
        this->lemmingStats_->setAmountOut(--this->amountOut);
    }
} // Lemmings