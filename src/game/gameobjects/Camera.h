//
// Created by filip on 2024-12-23.
//

#pragma once
#include "../../engine/Core.h"
#include "../../engine/GameObject.h"
#include "SFML/System/Vector2.hpp"

namespace Lemmings {

class Camera final : public Engine::GameObject{
private:
    sf::View view_;
    sf::Vector2f position_;
    const sf::Vector2f HALF_SCREEN_SIZE = {Engine::Core::DESIGNED_RESOLUTION_WIDTH / 2, Engine::Core::DESIGNED_RESOLUTION_HEIGHT / 2};
    const std::function<void()> WINDOW_RESIZED_HANDLER = [this] { this->windowResized(); };

public:
    static Engine::Event<Camera*> movedEvent;

    ~Camera() override;
    
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    void activate() const;
    sf::Vector2f position() const;
    void setPosition(sf::Vector2f newPos);
    void windowResized();
    void updateView(int windowWidth, int windowHeight);
};

} // Lemmings
