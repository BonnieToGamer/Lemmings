//
// Created by filip on 2024-12-25.
//

#include "Cursor.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "../../engine/Core.h"
#include "SFML/Window/Mouse.hpp"

namespace Lemmings {
    Cursor::Cursor(LemmingsHandler* lemmingHandler, Camera* cam, GameUI* ui) : lemmingsHandler_(lemmingHandler), camera_(cam), ui_(ui)
    {
    }

    void Cursor::init()
    {
        this->texture_ = Engine::Core::contentManager->getTexture("cursor");
        
        this->sprite_.setTexture(*this->texture_);
        this->sprite_.setTextureRect({0, 0, 16, 16});

        Engine::Core::Instance()->getWindow()->setMouseCursorVisible(false);
    }

    void Cursor::update(float delta)
    {
        if (this->wasMouseHeldLastFrame && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
            this->wasMouseHeldLastFrame = false;
        
        const sf::Vector2f mousePos = this->updateCursor();
        const sf::FloatRect mouseRect = this->createMouseRect(mousePos);

        const std::vector<Lemming*> lemmings = this->lemmingsHandler_->checkCollision(mouseRect);

        this->updateSpriteTexture(mouseRect, lemmings.size() > 0);
        this->updateCameraPosition(mousePos);
        this->checkAssignJob(lemmings);
        this->showCurrentLemmingStats(lemmings);
    }

    void Cursor::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->sprite_);
    }

    sf::Vector2f Cursor::updateCursor()
    {
        const sf::RenderWindow* window = Engine::Core::Instance()->getWindow();
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        mousePos.x = std::round(mousePos.x);
        mousePos.y = std::round(mousePos.y);
        this->sprite_.setPosition(mousePos.x - this->sprite_.getTextureRect().width / 2, mousePos.y - this->sprite_.getTextureRect().height / 2);

        return mousePos;
    }
    
    sf::FloatRect Cursor::createMouseRect(sf::Vector2f mousePos) const
    {
        return {
            mousePos.x - TEXTURE_WIDTH / 2,
            mousePos.y - TEXTURE_HEIGHT / 2,
            static_cast<float>(TEXTURE_WIDTH),
            static_cast<float>(TEXTURE_HEIGHT)
        };
    }

    void Cursor::updateSpriteTexture(sf::FloatRect mouseRect, bool collidedWithLemming)
    {
        if (collidedWithLemming) {
            this->sprite_.setTextureRect({16, 0, 16, 16}); // Collision texture
        } else {
            this->sprite_.setTextureRect({0, 0, 16, 16}); // Default texture
        }
    }

    void Cursor::updateCameraPosition(sf::Vector2f mousePos)
    {
        const sf::Vector2f cameraPos = this->camera_->position();

        if (isMouseNearLeftBoundary(mousePos, cameraPos)) {
            this->camera_->setPosition({cameraPos.x - this->CAMERA_MOVE_SPEED, cameraPos.y});
        } else if (isMouseNearRightBoundary(mousePos, cameraPos)) {
            this->camera_->setPosition({cameraPos.x + this->CAMERA_MOVE_SPEED, cameraPos.y});
        }
    }

    void Cursor::checkAssignJob(const std::vector<Lemming*>& lemmings)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false || lemmings.empty() || this->wasMouseHeldLastFrame)
            return;

        this->wasMouseHeldLastFrame = true;

        const Job job = this->ui_->getCurrentJob();

        if (job == Job::Nothing || !this->ui_->canAssignCurrentJob())
            return;
        
        bool success = false;
        int index = 0;
        while (!success && index < lemmings.size())
        {
            success = lemmings[index++]->tryAssignJob(job);
        }
        
        if (success)
            this->ui_->decreaseCurrentJob();
    }

    void Cursor::showCurrentLemmingStats(const std::vector<Lemming*>& lemmings) const
    {
        const uint amount = lemmings.size();
        const Job firstJob = lemmings.empty() ? Job::Nothing : lemmings.front()->getCurrentJob();

        this->ui_->setLemmingJobStat(amount, firstJob);
    }

    bool Cursor::isMouseNearLeftBoundary(sf::Vector2f mousePos, sf::Vector2f cameraPos) const
    {
        return mousePos.x - cameraPos.x <= this->CAMERA_MOVE_BOUNDARY &&
           mousePos.x > cameraPos.x &&
           mousePos.y >= cameraPos.y &&
           mousePos.y < cameraPos.y + Engine::Core::DESIGNED_RESOLUTION_HEIGHT;
    }

    bool Cursor::isMouseNearRightBoundary(sf::Vector2f mousePos, sf::Vector2f cameraPos) const
    {
        return mousePos.x >= cameraPos.x + Engine::Core::DESIGNED_RESOLUTION_WIDTH - this->CAMERA_MOVE_BOUNDARY &&
           mousePos.x < cameraPos.x + Engine::Core::DESIGNED_RESOLUTION_WIDTH &&
           mousePos.y >= cameraPos.y &&
           mousePos.y < cameraPos.y + Engine::Core::DESIGNED_RESOLUTION_HEIGHT;

    }
} // Lemmings