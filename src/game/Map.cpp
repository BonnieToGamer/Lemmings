//
// Created by filip on 2024-12-16.
//

#include "Map.h"

#include "../engine/Core.h"
#include "SFML/Window/Mouse.hpp"

namespace Lemmings {
    Map::Map(const std::string& mapName) : modifiableTexture_(mapName), nodes_()
    {
        int size = this->modifiableTexture_.width() * this->modifiableTexture_.height();
        this->nodes_.reserve(size);
        
        for (int y = 0; y < this->modifiableTexture_.height(); y++)
        {
            for (int x = 0; x < this->modifiableTexture_.width(); x++)
            {
                const sf::Color color = this->modifiableTexture_.getPixel(x, y);
                const int index = x + y * this->modifiableTexture_.width();
                
                std::unique_ptr<Node> node = std::make_unique<Node>(sf::Vector2i(x, y), color.a != 0);
                this->nodes_.emplace_back(std::move(node));
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

    Node& Map::operator[](int index)
    {
        this->nodesAccessed_ = true;
        this->accessedQueue_.push(index);
        return *this->nodes_[index];
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

                if (this->nodes_[index]->isEnabled())
                    return;

                const uint x = index % this->modifiableTexture_.width();
                const uint y = index / this->modifiableTexture_.width();
                
                this->modifiableTexture_.setPixel(x, y, sf::Color::Transparent);
            }

            this->modifiableTexture_.updateTexture();
        }
    } 

    void Map::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->modifiableTexture_.getSprite());
    }
} // Lemmings