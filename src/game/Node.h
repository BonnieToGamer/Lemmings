//
// Created by filip on 2024-12-16.
//

#pragma once
#include "SFML/System/Vector2.hpp"

namespace Lemmings {

class Node {
private:
    sf::Vector2i position_;
    bool enabled_;

public:
    Node(sf::Vector2i position, bool enabled);
    bool isEnabled() const;
};

} // Lemmings
