//
// Created by filip on 2024-12-23.
//

#include "Camera.h"

#include "../engine/Core.h"

namespace Lemmings {
    void Camera::init()
    {
        this->view_ = sf::View(sf::FloatRect(
            0,
            0,
            Engine::Core::DESIGNED_RESOLUTION_WIDTH,
            Engine::Core::DESIGNED_RESOLUTION_HEIGHT)
        );
    }

    void Camera::update(float delta)
    {
    }

    void Camera::draw(sf::RenderTarget& renderTarget)
    {
        this->activate();
    }

    void Camera::activate() const
    {
        Engine::Core::Instance()->getWindow()->setView(this->view_);
    }

    sf::Vector2f Camera::position() const
    {
        return this->view_.getCenter() - HALF_SCREEN_SIZE;
    }

    void Camera::setPosition(sf::Vector2f newPos)
    {
        this->view_.setCenter(
            newPos.x + HALF_SCREEN_SIZE.x,
            newPos.y + HALF_SCREEN_SIZE.y
        );
    }
} // Lemmings