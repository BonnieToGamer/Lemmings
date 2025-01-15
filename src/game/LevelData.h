//
// Created by filip on 2024-12-26.
//

#pragma once
#include <string>
#include <map>

#include "SFML/Graphics/Color.hpp"

namespace Lemmings {

struct LevelData {
public:
    enum DirtIndexColor
    {
        dirt = 0,
        sand = 1,
        quartz = 2,
        ice = 3,
        stone = 4
    };
        
    uint levelNum;
    std::string name;
    std::string image;
    uint dirtIndex;
    uint exitIndex;
    uint timeLimit;
    uint saveRequirement;
    uint amountOfLemmings;
    uint releaseRate;
    uint climbers;
    uint floaters;
    uint bombers;
    uint blockers;
    uint builders;
    uint bashers;
    uint miners;
    uint diggers;
    int spawnX;
    int spawnY;
    int exitX;
    int exitY;
    uint cameraX;
    uint cameraY;

    inline static const std::map<DirtIndexColor, sf::Color> indexToColor = {
        {dirt, sf::Color(120, 77, 0)},
        {sand, sf::Color::Yellow},
        {quartz, sf::Color::White},
        {ice, sf::Color::Blue},
        {stone, sf::Color(128, 128, 128)}
    };
};


} // Lemmings