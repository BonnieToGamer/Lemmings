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
public:
    enum Job
    {
        Walker,
        Faller,
        Digger
    };
    
private:
    sf::Vector2f position_;
    std::shared_ptr<Engine::AnimatedTexture> currentAnimatedTexture_;
    std::unique_ptr<Engine::StateMachineManager<Lemming>> stateMachineManager_;
    std::shared_ptr<Map> map_;
    std::unordered_map<Job, std::shared_ptr<Engine::AnimatedTexture>> animations_;
    int currentDir_ = 1;

    const uint TEXTURE_WIDTH = 16;
    const uint TEXTURE_HEIGHT = 16;
    
public:    
    explicit Lemming(const std::shared_ptr<Map>& map);

    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    const sf::Vector2f& getPosition();
    void setPosition(const sf::Vector2f& newPos);
    const std::shared_ptr<Map>& map();
    void playAnimation(Job job);
    void flipSprite() const;
    bool checkCollision(float x, float y) const;
    int dir() const;
    void setDir(int newDir);
};

} // Lemmings
