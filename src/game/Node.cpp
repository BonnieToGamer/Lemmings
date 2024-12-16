//
// Created by filip on 2024-12-16.
//

#include "Node.h"

namespace Lemmings {
    Node::Node(sf::Vector2i position, bool enabled) : position_(position), enabled_(enabled)
    { }

    bool Node::isEnabled() const
    {
        return this->enabled_;
    }
} // Lemmings