//
// Created by filip on 2025-01-09.
//

#pragma once
#include <memory>
#include <string>

namespace Lemmings::Engine::Asset {

class GameAsset {    
public:
    explicit GameAsset(const std::string& fileName) {};
    virtual ~GameAsset() = default;
};
} // Lemmings
