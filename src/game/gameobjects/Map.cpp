//
// Created by filip on 2024-12-16.
//

#include "Map.h"

#include "../../engine/Core.h"
#include "SFML/Window/Mouse.hpp"

namespace Lemmings {
    Map::Map(const std::string& mapName) : modifiableTexture_(mapName), nodes_()
    {
        const int size = this->modifiableTexture_.width() * this->modifiableTexture_.height();
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

    unsigned int Map::width()
    {
        return this->modifiableTexture_.width();
    }

    unsigned int Map::height()
    {
        return this->modifiableTexture_.height();
    }

    const Node& Map::operator[](int index) const
    {
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
                const unsigned int index = this->accessedQueue_.front();
                this->accessedQueue_.pop();

                const unsigned int x = index % this->modifiableTexture_.width();
                const unsigned int y = index / this->modifiableTexture_.width();
                
                this->modifiableTexture_.setPixel(x, y, this->nodes_[index]->getColor());
            }

            this->modifiableTexture_.updateTexture();
        }
    } 

    void Map::draw(sf::RenderTarget& renderTarget)
    {
        renderTarget.draw(this->modifiableTexture_.getSprite());
    }

    void Map::changeNode(int index, bool value, sf::Color color, HorizontalDirection oneWay)
    {
        this->nodesAccessed_ = true;
        this->accessedQueue_.push(index);
        this->nodes_[index]->setEnabled(value);
        this->nodes_[index]->setColor(color);
        this->nodes_[index]->setOneWay(oneWay);
    }
} // Lemmings