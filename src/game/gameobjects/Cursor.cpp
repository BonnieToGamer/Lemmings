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
    Cursor::Cursor(std::shared_ptr<LemmingsHandler> lemmingHandler, std::shared_ptr<Camera> cam, std::shared_ptr<GameUI> ui) : lemmingsHandler_(std::move(lemmingHandler)), camera_(std::move(cam)), ui_(std::move(ui))
    {
    }

    void Cursor::init()
    {
        if(!this->texture_.loadFromFile(ASSETS_PATH"cursor.png"))
            throw std::runtime_error("Couldn't load texture cursor.png");

        this->sprite_.setTexture(this->texture_);
        this->sprite_.setTextureRect({0, 0, 16, 16});

        Engine::Core::Instance()->getWindow()->setMouseCursorVisible(false);
    }

    void Cursor::update(float delta)
    {
        if (this->wasMouseHeldLastFrame && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
            this->wasMouseHeldLastFrame = false;
        
        const sf::Vector2f mousePos = this->updateCursor();
        const sf::FloatRect mouseRect = this->createMouseRect(mousePos);

        std::vector<Lemming*> lemmings = this->lemmingsHandler_->checkCollision(mouseRect);

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
        sf::RenderWindow* window = Engine::Core::Instance()->getWindow();
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        mousePos.x = std::round(mousePos.x);
        mousePos.y = std::round(mousePos.y);
        this->sprite_.setPosition(mousePos.x - this->sprite_.getTextureRect().width / 2, mousePos.y - this->sprite_.getTextureRect().height / 2);

        return mousePos;
    }
    
    sf::FloatRect Cursor::createMouseRect(sf::Vector2f mousePos)
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

        Job job = this->ui_->getCurrentJob();

        if (job == Job::Nothing)
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

    void Cursor::showCurrentLemmingStats(const std::vector<Lemming*>& lemmings)
    {
        uint amount = lemmings.size();
        Job firstJob = lemmings.empty() ? Job::Nothing : lemmings.front()->getCurrentJob();

        this->ui_->setLemmingJobStat(amount, firstJob);
    }

    bool Cursor::isMouseNearLeftBoundary(sf::Vector2f mousePos, sf::Vector2f cameraPos)
    {
        return mousePos.x - cameraPos.x <= this->CAMERA_MOVE_BOUNDARY &&
           mousePos.x > cameraPos.x &&
           mousePos.y >= cameraPos.y &&
           mousePos.y < cameraPos.y + Engine::Core::DESIGNED_RESOLUTION_HEIGHT;
    }

    bool Cursor::isMouseNearRightBoundary(sf::Vector2f mousePos, sf::Vector2f cameraPos)
    {
        return mousePos.x >= cameraPos.x + Engine::Core::DESIGNED_RESOLUTION_WIDTH - this->CAMERA_MOVE_BOUNDARY &&
           mousePos.x < cameraPos.x + Engine::Core::DESIGNED_RESOLUTION_WIDTH &&
           mousePos.y >= cameraPos.y &&
           mousePos.y < cameraPos.y + Engine::Core::DESIGNED_RESOLUTION_HEIGHT;

    }
} // Lemmings