//
// Created by filip on 2024-12-16.
//

#include "Map.h"

#include "../engine/Core.h"
#include "SFML/Window/Mouse.hpp"

namespace Lemmings {
    Map::Map(const std::string& mapName) : modifiableTexture_(mapName), nodes_()
    {
        nodes_.reserve(this->modifiableTexture_.width() * this->modifiableTexture_.height());
        
        for (int y = 0; y < this->modifiableTexture_.height(); y++)
        {
            for (int x = 0; x < this->modifiableTexture_.width(); x++)
            {
                const sf::Color color = this->modifiableTexture_.getPixel(x, y);
                const int index = x + y * this->modifiableTexture_.width();

                nodes_[index] = Node(sf::Vector2i(x, y), color.a != 0);
            }
        }
    }

    uint Map::width()
    {
        return this->modifiableTexture_.width();
    }

    uint Map::height()
    {
        return this->modifiableTexture_.height();
    }

    const Node& Map::operator[](int index)
    {
        this->nodesAccessed_ = true;
        this->accessedQueue_.push(index);
        return this->nodes_[index];
    }

    void Map::init()
    {
    }

    void Map::update(float delta)
    {
        if (this->nodesAccessed_)
        {
            while (!this->accessedQueue_.empty())
            {
                const uint index = this->accessedQueue_.front();
                this->accessedQueue_.pop();

                if (this->nodes_[index].isEnabled())
                    return;

                const uint x = index % this->modifiableTexture_.width();
                const uint y = index / this->modifiableTexture_.height();
                
                this->modifiableTexture_.setPixel(x, y, sf::Color::Transparent);
            }
        }
    } 

    void Map::draw(sf::RenderTexture& renderTexture)
    {
        renderTexture.draw(this->modifiableTexture_.getSprite());
    }
} // Lemmings