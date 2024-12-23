//
// Created by filip on 2024-12-23.
//

#pragma once
#include <vector>
#include "Lemming.h"

namespace Lemmings {

class LemmingsHandler final : public Engine::GameObject {
private:
    std::vector<std::shared_ptr<Lemming>> lemmings_;
    Engine::Timer fixedUpdateTimer_;
    std::shared_ptr<Map> map_;

public:
    explicit LemmingsHandler(const std::shared_ptr<Map>& map);
    void init() override;
    void update(float delta) override;
    void draw(sf::RenderTarget& renderTarget) override;

    void addLemming(sf::Vector2i position);
};

} // Lemmings
