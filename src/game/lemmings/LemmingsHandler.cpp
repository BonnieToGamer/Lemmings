//
// Created by filip on 2024-12-23.
//

#include "LemmingsHandler.h"

namespace Lemmings {
    LemmingsHandler::LemmingsHandler(const std::shared_ptr<Map>& map): fixedUpdateTimer_(0.0667f), map_(map)
    {
    }

    void LemmingsHandler::init()
    {
        for (auto& lemming : this->lemmings_)
            lemming->init();
    }

    void LemmingsHandler::update(float delta)
    {
        const bool shouldUpdate = this->fixedUpdateTimer_.update(delta);
        
        for (auto& lemming : this->lemmings_)
        {            
            if (shouldUpdate)
                lemming->update(delta);
        }
    }

    void LemmingsHandler::draw(sf::RenderTarget& renderTarget)
    {
        for (auto& lemming : this->lemmings_)
            lemming->draw(renderTarget);
    }

    void LemmingsHandler::addLemming(sf::Vector2i position)
    {
        this->lemmings_.emplace_back(std::make_shared<Lemming>(this->map_));
        this->lemmings_.back()->setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
    }
} // Lemmings