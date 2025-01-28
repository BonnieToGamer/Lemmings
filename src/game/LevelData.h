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
        
    unsigned int levelNum;
    std::string name;
    std::string image;
    unsigned int dirtIndex;
    unsigned int exitIndex;
    unsigned int timeLimit;
    unsigned int saveRequirement;
    unsigned int amountOfLemmings;
    unsigned int releaseRate;
    unsigned int climbers;
    unsigned int floaters;
    unsigned int bombers;
    unsigned int blockers;
    unsigned int builders;
    unsigned int bashers;
    unsigned int miners;
    unsigned int diggers;
    int spawnX;
    int spawnY;
    int exitX;
    int exitY;
    unsigned int cameraX;
    unsigned int cameraY;

    inline static const std::map<DirtIndexColor, sf::Color> indexToColor = {
        {dirt, sf::Color(120, 77, 0)},
        {sand, sf::Color::Yellow},
        {quartz, sf::Color::White},
        {ice, sf::Color::Blue},
        {stone, sf::Color(128, 128, 128)}
    };
};


} // Lemmings