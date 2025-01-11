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

    void Node::setEnabled(bool value)
    {
        this->enabled_ = value;
    }

    sf::Color Node::getColor()
    {
        return this->color_;
    }

    void Node::setColor(sf::Color color)
    {
        this->color_ = color;
    }
} // Lemmings