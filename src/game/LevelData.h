//
// Created by filip on 2024-12-26.
//

#pragma once
#include <string>

namespace Lemmings {

struct LevelData {
public:
    uint levelNum;
    std::string name;
    std::string image;
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
};

} // Lemmings