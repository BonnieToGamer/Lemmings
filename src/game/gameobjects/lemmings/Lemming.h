//
// Created by filip on 2024-12-16.
//

#pragma once

#include <unordered_map>

#include "../Map.h"
#include "../../LevelData.h"
#include "../../../engine/AnimationManager.h"
#include "../../../engine/Event.h"
#include "../../../engine/GameObject.h"
#include "../../../engine/SpriteSheetAnimation.h"
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
    Nothing = 10,
    Winner = 11
};

enum Direction
{
    Right = 1,
    Left = -1,
};
    
class Lemming : public Engine::GameObject {
private:
    Map* map_;
    LevelData* data_;
    sf::Vector2i position_;
    
    Engine::AnimationManager<Job> animations_;
    Engine::AnimationManager<Job> dirtAnimations_;
    std::unique_ptr<Engine::SpriteSheet> lemmingSpriteSheet;
    std::unique_ptr<Engine::SpriteSheet> dirtSpriteSheet;
    
    std::unique_ptr<Engine::StateMachineManager<Lemming>> stateMachineManager_;
    
    Direction currentDir_ = Right;
    Job currentJob_ = Faller;
    
    const uint TEXTURE_WIDTH = 16;
    const uint TEXTURE_HEIGHT = 16;

    sf::Texture* lemmingTexture_;
    sf::Texture* dirtTexture_;

    void addAnimation(Job job, uint amountOfFrames, const sf::Vector2u& offset, bool addDirt);
    void die();
    
public:
    static Engine::Event<Lemming*> deathEvent; 
    static Engine::Event<Lemming*> winEvent; 
    
    explicit Lemming(Map* map, LevelData* data);

    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;
    sf::Vector2i getPosition() const;
    void setPosition(const sf::Vector2i& newPos);
    Map* map();
    void initJob(Job job, sf::Vector2i offset);
    void flipSprite();
    Direction dir() const;
    void setDir(Direction newDir);
    sf::Vector2i getActualPos();
    sf::Vector2i getSize();
    Job getCurrentJob() const;
    bool tryAssignJob(Job job) const;
    void win();

    void checkCollisionExit();
    bool checkCollision(int x, int y) const;
    void tryDig(int x, int y) const;
    void placeCell(int x, int y, sf::Color color) const;
};

} // Lemmings
