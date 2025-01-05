//
// Created by filip on 2024-12-23.
//

#include "LemmingsHandler.h"

#include <utility>

namespace Lemmings {
    void LemmingsHandler::onLemmingDeath(Lemming* lemming)
    {
        auto it = std::remove_if(this->lemmings_.begin(), this->lemmings_.end(),
        [lemming](const std::unique_ptr<Lemming>& ptr) {
            return ptr.get() == lemming; // Compare the raw pointer
        });

        this->lemmings_.erase(it, this->lemmings_.end());
    }

    LemmingsHandler::LemmingsHandler(Map* map): fixedUpdateTimer_(0.0667f), map_(map)
    {
    }

    LemmingsHandler::~LemmingsHandler()
    {
        Lemming::deathEvent -= LEMMING_DEATH_HANDLER;
    }

    void LemmingsHandler::init()
    {
        Lemming::deathEvent += LEMMING_DEATH_HANDLER;
        for (auto& lemming : this->lemmings_)
        {
            lemming->init();
        }
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
        this->lemmings_.emplace_back(std::make_unique<Lemming>(this->map_));
        this->lemmings_.back()->setPosition({position.x, position.y});
        this->lemmings_.back()->init();
    }

    std::vector<Lemming*> LemmingsHandler::checkCollision(sf::FloatRect rect)
    {
        std::vector<Lemming*> collidingLemmings;
        for (auto& lemming : lemmings_)
        {
            sf::Vector2i lemmingPos = lemming->getActualPos();
            sf::Vector2i lemmingSize = lemming->getSize();
            sf::FloatRect lemmingRect = sf::FloatRect(lemmingPos.x, lemmingPos.y, lemmingSize.x, lemmingSize.y);

            if (lemmingRect.intersects(rect))
                collidingLemmings.push_back(lemming.get());
        }

        return collidingLemmings;
    }
} // Lemmings