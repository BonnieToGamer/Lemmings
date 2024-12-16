//
// Created by filip on 2024-12-16.
//

#pragma once

#include <unordered_map>

#include "../Map.h"
#include "../../engine/AnimatedTexture.h"
#include "../../engine/GameObject.h"
#include "../../engine/StateMachineManager.h"
#include "../../engine/Timer.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings {

class Lemming : public Engine::GameObject, public std::enable_shared_from_this<Lemming> {
private:
    sf::Vector2f position_;
    std::shared_ptr<Engine::AnimatedTexture> currentAnimatedTexture_;
    std::unique_ptr<Engine::StateMachineManager<Lemming>> stateMachineManager_;
    std::shared_ptr<Map> map_;
    Engine::Timer fixedUpdateTimer_ = Engine::Timer(1.f / 30.f);
    std::unordered_map<std::string, std::shared_ptr<Engine::AnimatedTexture>> animations_;

    const uint TEXTURE_WIDTH = 8;
    const uint TEXTURE_HEIGHT = 8;
    
public:
    explicit Lemming(const std::shared_ptr<Map>& map);

    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTexture& renderTexture) override;
    const sf::Vector2f& getPosition();
    void setPosition(const sf::Vector2f& newPos);
    const std::shared_ptr<Map>& map();
    void playAnimation(const std::string& name);
};

} // Lemmings
