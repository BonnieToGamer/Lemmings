//
// Created by filip on 2024-12-16.
//

#include "Core.h"

#include <sys/stat.h>

#include "../game/scenes/Level.h"

namespace Lemmings::Engine
{
    Core* Core::INSTANCE = nullptr;
    Core::Core() : sceneManager_(), renderTexture_(), renderSprite_()
    {
        INSTANCE = this;
        uint width = DESIGNED_RESOLUTION_WIDTH * 4;
        uint height = DESIGNED_RESOLUTION_HEIGHT * 4;
        this->renderWindow_ = std::make_unique<sf::RenderWindow>(sf::VideoMode{width, height}, "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close);
        this->renderWindow_->setFramerateLimit(60);
    
        uint displayWidth = sf::VideoMode::getDesktopMode().width;
        uint displayHeight = sf::VideoMode::getDesktopMode().height;
        this->renderWindow_->setPosition(sf::Vector2i(
            static_cast<int>((displayWidth - width) / 2),
            static_cast<int>((displayHeight - height) / 2))
        );


        if (!this->renderTexture_.create(DESIGNED_RESOLUTION_WIDTH, DESIGNED_RESOLUTION_HEIGHT))
            throw std::runtime_error("Couldn't create render texture");
        
        this->sceneManager_.addScene(std::make_shared<Scene::Level>());
        this->windowResized();
    }

    void Core::run()
    {
        sf::Clock clock;
        while (renderWindow_->isOpen())
        {
            sf::Time elapsed = clock.restart();
            this->update(elapsed.asSeconds());
            this->draw();
        }
    }

    void Core::update(const float delta)
    {
        for (auto event = sf::Event(); renderWindow_->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                renderWindow_->close();

            else if (event.type == sf::Event::Resized)
                this->windowResized();
        }

        if (const std::shared_ptr<IScene> scene = this->sceneManager_.getCurrentScene())
            scene->update(delta);
    }

    void Core::draw()
    {
        this->renderTexture_.clear(sf::Color::White);
        if (std::shared_ptr<IScene> scene = this->sceneManager_.getCurrentScene())
            scene->draw(this->renderTexture_);
        this->renderTexture_.display();

        this->renderSprite_.setTexture(this->renderTexture_.getTexture());
        
        renderWindow_->clear(sf::Color(100, 149, 237));
        this->renderWindow_->draw(this->renderSprite_);
        renderWindow_->display();
    }

    int Core::getScale()
    {
        // TODO: THIS METHOD
        return 4;
    }

    sf::RenderWindow* Core::getWindow()
    {
        return this->renderWindow_.get();
    }

    sf::FloatRect Core::getScaleRectangle() const
    {
        // TODO: THIS METHOD
        return {0, 0, 4, 4};
    }

    void Core::windowResized()
    {
        const sf::FloatRect scaleRect = this->getScaleRectangle();
        this->renderSprite_.setPosition(scaleRect.getPosition().x, scaleRect.getPosition().y);
        this->renderSprite_.setScale(scaleRect.width, scaleRect.height);
    }
}
