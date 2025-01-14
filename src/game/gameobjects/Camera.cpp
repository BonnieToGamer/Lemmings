//
// Created by filip on 2024-12-23.
//

#include "Camera.h"

#include "../../engine/Core.h"
#include <math.h>

namespace Lemmings {
    Engine::Event<Camera*> Camera::movedEvent;

    Camera::~Camera()
    {
        Engine::Core::windowSizeChangedEvent -= this->WINDOW_RESIZED_HANDLER;
    }

    void Camera::init()
    {
        Engine::Core::windowSizeChangedEvent += this->WINDOW_RESIZED_HANDLER;
        
        this->view_ = sf::View(sf::FloatRect(
            0,
            0,
            Engine::Core::DESIGNED_RESOLUTION_WIDTH,
            Engine::Core::DESIGNED_RESOLUTION_HEIGHT)
        );

        this->position_ = this->view_.getCenter() - HALF_SCREEN_SIZE;
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
        return this->position_;
    }

    void Camera::setPosition(sf::Vector2f newPos)
    {
        this->position_ = newPos;
        this->view_.setCenter(
            std::round(newPos.x) + HALF_SCREEN_SIZE.x,
            std::round(newPos.y) + HALF_SCREEN_SIZE.y
        );
        movedEvent.invoke(this);
    }

    void Camera::windowResized()
    {
        sf::Vector2u windowSize = Engine::Core::Instance()->getWindow()->getSize();
        this->updateView(windowSize.x, windowSize.y);
    }

    void Camera::updateView(int windowWidth, int windowHeight)
    {
        // Compares the aspect ratio of the window to the aspect ratio of the view,
        // and sets the view's viewport accordingly in order to achieve a letterbox effect.
        // A new view (with a new viewport set) is returned.

        float windowRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
        float viewRatio = this->view_.getSize().x / static_cast<float>(this->view_.getSize().y);
        float sizeX = 1;
        float sizeY = 1;
        float posX = 0;
        float posY = 0;

        bool horizontalSpacing = true;
        if (windowRatio < viewRatio)
            horizontalSpacing = false;

        // If horizontalSpacing is true, the black bars will appear on the left and right side.
        // Otherwise, the black bars will appear on the top and bottom.

        if (horizontalSpacing) {
            sizeX = viewRatio / windowRatio;
            posX = (1 - sizeX) / 2.f;
        }

        else {
            sizeY = windowRatio / viewRatio;
            posY = (1 - sizeY) / 2.f;
        }

        this->view_.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
    }
} // Lemmings