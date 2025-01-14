//
// Created by filip on 2024-12-23.
//

#include "LemmingsHandler.h"

namespace Lemmings {
    Engine::Event<> LemmingsHandler::lemmingWinEvent;
    
    void LemmingsHandler::onLemmingDeath(Lemming* lemming)
    {
        this->removalQueue_.push(lemming);
    }

    void LemmingsHandler::onLemmingWin(Lemming* lemming)
    {
        this->removalQueue_.push(lemming);
        lemmingWinEvent.invoke();
    }

    void LemmingsHandler::processRemovalQueue()
    {
        while (!this->removalQueue_.empty())
        {
            auto lemming = this->removalQueue_.front();
            this->removalQueue_.pop();
            
            auto it = std::remove_if(this->lemmings_.begin(), this->lemmings_.end(),
            [lemming](const std::unique_ptr<Lemming>& ptr) {
                return ptr.get() == lemming; // Compare the raw pointer
            });

            this->lemmings_.erase(it, this->lemmings_.end());
        }
    }

    LemmingsHandler::LemmingsHandler(Map* map, LevelData* data): fixedUpdateTimer_(0.0667f), map_(map), data_(data)
    {
    }

    LemmingsHandler::~LemmingsHandler()
    {
        Lemming::deathEvent -= LEMMING_DEATH_HANDLER;
        Lemming::winEvent -= LEMMING_WIN_HANDLER;
    }

    void LemmingsHandler::init()
    {
        Lemming::deathEvent += LEMMING_DEATH_HANDLER;
        Lemming::winEvent += LEMMING_WIN_HANDLER;
        for (const auto& lemming : this->lemmings_)
        {
            lemming->init();
        }
    }

    void LemmingsHandler::update(float delta)
    {
        const bool shouldUpdate = this->fixedUpdateTimer_.update(delta);
        if (!shouldUpdate)
            return;
        
        for (const auto& lemming : this->lemmings_)
            lemming->update(delta);

        this->processRemovalQueue();
    }

    void LemmingsHandler::draw(sf::RenderTarget& renderTarget)
    {
        for (const auto& lemming : this->lemmings_)
            lemming->draw(renderTarget);
    }

    void LemmingsHandler::addLemming(sf::Vector2i position)
    {
        this->lemmings_.emplace_back(std::make_unique<Lemming>(this->map_, this->data_));
        this->lemmings_.back()->init();
        this->lemmings_.back()->setPosition({position.x, position.y});
    }

    std::vector<Lemming*> LemmingsHandler::checkCollision(sf::FloatRect rect) const
    {
        std::vector<Lemming*> collidingLemmings;
        for (auto& lemming : lemmings_)
        {
            const sf::Vector2i lemmingPos = lemming->getActualPos();
            const sf::Vector2i lemmingSize = lemming->getSize();

            if (auto lemmingRect = sf::FloatRect(lemmingPos.x, lemmingPos.y, lemmingSize.x, lemmingSize.y); lemmingRect.intersects(rect))
                collidingLemmings.push_back(lemming.get());
        }

        return collidingLemmings;
    }

    uint LemmingsHandler::getAmountOfLemmings() const
    {
        return this->lemmings_.size();
    }
} // Lemmings