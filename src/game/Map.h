//
// Created by filip on 2024-12-16.
//

#pragma once
#include <queue>

#include "Node.h"
#include "../engine/GameObject.h"
#include "../engine/ModifiableTexture.h"

namespace Lemmings {

class Map final : public Engine::GameObject {
private:
    Engine::ModifiableTexture modifiableTexture_;
    std::vector<Node> nodes_;
    bool nodesAccessed_ = false;
    std::queue<int> accessedQueue_;

public:
    explicit Map(const std::string& mapName);

    uint width();
    uint height();
    
    const Node& operator[](int index);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTexture& renderTexture) override;
};

} // Lemmings
