//
// Created by filip on 2024-12-16.
//

#include "Core.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

#include "../game/scenes/EndScene.h"
#include "../game/scenes/Level.h"
#include "../game/scenes/LevelLoader.h"

namespace Lemmings::Engine
{
    Core* Core::INSTANCE = nullptr;
    Event<> Core::windowSizeChangedEvent = Event<>();
    std::unique_ptr<Asset::ContentManager> Core::contentManager = std::make_unique<Asset::ContentManager>();

    void Core::loadNewLevel(uint levelIndex)
    {
        if (levelIndex > this->levels_.size())
        {
            this->sceneManager_.addScene(std::make_unique<Scene::EndScene>());
            return;
        }
        
        std::string levelPath = this->levels_[levelIndex];
        this->sceneManager_.addScene(std::make_unique<Scene::Level>(levelPath));
    }

    void Core::loadLevelIndices()
    {
        for (const auto & entry : std::filesystem::directory_iterator(ASSETS_PATH"levels/"))
        {
            std::string path = entry.path();
            
            std::ifstream file(path);
            std::string line;
            char* endPtr;
            
            std::getline(file, line);

            uint index = std::strtol(line.c_str(), &endPtr, 10);

            if (endPtr == line.c_str()) {
                // No conversion was performed
                throw std::runtime_error("No digits were found in the input string.");
            }
            if (errno == ERANGE) {
                // The value is out of range for long
                throw std::runtime_error("The number is out of range.");
            }
            if (*endPtr != '\0') {
                // There are leftover characters after the number
                throw std::runtime_error("Additional characters after number: " + std::string(endPtr));
            }

            this->levels_[index] = path;
        }
    }

    Core::Core() : sceneManager_(), renderTexture_(), renderSprite_()
    {
        INSTANCE = this;
        const uint width = DESIGNED_RESOLUTION_WIDTH * 4;
        const uint height = DESIGNED_RESOLUTION_HEIGHT * 4;
        this->renderWindow_ = std::make_unique<sf::RenderWindow>(sf::VideoMode{width, height}, "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close);
        this->renderWindow_->setFramerateLimit(60);

        const uint displayWidth = sf::VideoMode::getDesktopMode().width;
        const uint displayHeight = sf::VideoMode::getDesktopMode().height;
        this->renderWindow_->setPosition(sf::Vector2i(
            static_cast<int>((displayWidth - width) / 2),
            static_cast<int>((displayHeight - height) / 2))
        );


        if (!this->renderTexture_.create(DESIGNED_RESOLUTION_WIDTH, DESIGNED_RESOLUTION_HEIGHT))
            throw std::runtime_error("Couldn't create render texture");

        this->loadLevelIndices();

        Scene::LevelLoader::changeLevelEvent += CHANGE_LEVEL_EVENT;
        this->sceneManager_.addScene(std::make_unique<Scene::LevelLoader>());
    }

    Core::~Core()
    {
        Scene::LevelLoader::changeLevelEvent -= CHANGE_LEVEL_EVENT;
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

        this->sceneManager_.removeScene();
        contentManager = nullptr;
    }

    void Core::update(const float delta)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (!this->slowTimer_.update(delta))
                return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            return;
        
        
        for (auto event = sf::Event(); renderWindow_->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                renderWindow_->close();
            else if (event.type == sf::Event::Resized)
                windowSizeChangedEvent.invoke();
        }

        if (IScene* scene = this->sceneManager_.getCurrentScene())
            scene->update(delta);
    }

    void Core::draw()
    {
        renderWindow_->clear(sf::Color::Black);
        if (IScene* scene = this->sceneManager_.getCurrentScene())
            scene->draw(*this->renderWindow_);
        
        renderWindow_->display();
    }

    void Core::removeCurrentScene()
    {
        this->sceneManager_.removeScene();
    }

    sf::RenderWindow* Core::getWindow() const
    {
        return this->renderWindow_.get();
    }
}
