//
// Created by filip on 2024-12-25.
//

#pragma once
#include "Camera.h"
#include "GameUI.h"
#include "./lemmings/LemmingsHandler.h"
#include "../../engine/GameObject.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings {

    class Cursor final : public Engine::GameObject{
    private:
        sf::Texture* texture_;
        sf::Sprite sprite_;
        LemmingsHandler* lemmingsHandler_;
        Camera* camera_;
        GameUI* ui_;
        bool wasMouseHeldLastFrame = false;

        const unsigned int CAMERA_MOVE_SPEED = 5;
        const unsigned int CAMERA_MOVE_BOUNDARY = 5;
        const unsigned int TEXTURE_WIDTH = 14;
        const unsigned int TEXTURE_HEIGHT = 14;
        
        sf::Vector2f updateCursor();
        sf::FloatRect createMouseRect(sf::Vector2f mousePos) const;
        void updateSpriteTexture(sf::FloatRect mouseRect, bool collidedWithLemming);
        void updateCameraPosition(sf::Vector2f mousePos);
        void checkAssignJob(const std::vector<Lemming*>& lemmings);
        void showCurrentLemmingStats(const std::vector<Lemming*>& lemmings) const;
        bool isMouseNearLeftBoundary(sf::Vector2f mousePos, sf::Vector2f cameraPos) const;
        bool isMouseNearRightBoundary(sf::Vector2f mousePos, sf::Vector2f cameraPos) const;

    public:
        explicit Cursor(LemmingsHandler* lemmingHandler, Camera* cam, GameUI* ui);
        void init() override;
        void update(float delta) override;
        void draw(sf::RenderTarget& renderTarget) override;
    };

} // Lemmings
