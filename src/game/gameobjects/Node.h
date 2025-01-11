//
// Created by filip on 2024-12-16.
//

#pragma once
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

namespace Lemmings {

class Node {
private:
    sf::Vector2i position_;
    bool enabled_;
    sf::Color color_ = sf::Color::Transparent;

public:
    Node(sf::Vector2i position, bool enabled);
    bool isEnabled() const;
    void setEnabled(bool value);
    sf::Color getColor();
    void setColor(sf::Color color);
};

} // Lemmings
