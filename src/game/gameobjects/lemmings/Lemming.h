//
// Created by filip on 2024-12-16.
//

#pragma once

#include <unordered_map>

#include "../Map.h"
#include "../../../engine/AnimatedTexture.h"
#include "../../../engine/Event.h"
#include "../../../engine/GameObject.h"
#include "../../../engine/StateMachineManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Lemmings {

enum Job
{
    Walker = 0,
    Faller = 1,
    Climber = 2,
    Floater = 3,
    Bomber = 4,
    Blocker = 5,
    Builder = 6,
    Basher = 7,
    Miner = 8,
    Digger = 9,
    Nothing = 10
};

enum Direction
{
    Right = 1,
    Left = -1,
};
    
class Lemming : public Engine::GameObject {
private:
    Map* map_;
    sf::Vector2i position_;
    std::shared_ptr<Engine::AnimatedTexture> currentAnimatedTexture_;
    std::shared_ptr<Engine::AnimatedTexture> currentAnimatedDirtTexture_;
    std::unique_ptr<Engine::StateMachineManager<Lemming>> stateMachineManager_;
    std::unordered_map<Job, std::shared_ptr<Engine::AnimatedTexture>> animations_;
    std::unordered_map<Job, std::shared_ptr<Engine::AnimatedTexture>> dirtAnimations_;
    Direction currentDir_ = Right;
    Job currentJob_ = Job::Faller;
    
    const uint TEXTURE_WIDTH = 16;
    const uint TEXTURE_HEIGHT = 16;

    static std::shared_ptr<sf::Texture> lemmingTexture_;
    static std::shared_ptr<sf::Texture> dirtTexture_;

    void addAnimation(Job job, uint amountOfFrames, uint row, const sf::Vector2u& spriteSize, const sf::Vector2i& offset, std::shared_ptr<sf::Texture> texture, bool addDirt = false, std::shared_ptr<sf::Texture> dirtTexture = nullptr);
    void die();
    void loadTexture(std::shared_ptr<sf::Texture>& texture, const std::string& textureName);
    
public:
    static Engine::Event<Lemming*> deathEvent; 
    
    explicit Lemming(Map* map);

    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    const sf::Vector2i& getPosition();
    void setPosition(const sf::Vector2i& newPos);
    Map* map();
    void playAnimation(Job job);
    void setAnimationOffset(sf::Vector2i offset);
    void flipSprite();
    Direction dir() const;
    void setDir(Direction newDir);
    sf::Vector2i getActualPos();
    sf::Vector2i getSize();
    void forceUpdateNewJob(Job job);
    Job getCurrentJob() const;
    bool tryAssignJob(Job job) const;
    
    bool checkCollision(int x, int y) const;
    void tryDig(int x, int y) const;

    static void destroyTextures();
};

} // Lemmings
