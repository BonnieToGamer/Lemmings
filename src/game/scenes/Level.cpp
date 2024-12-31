//
// Created by filip on 2024-12-16.
//

#include "Level.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../gameobjects/Camera.h"
#include "../gameobjects/Cursor.h"
#include "../gameobjects/Map.h"
#include "../gameobjects/GameUI.h"
#include "../../engine/Core.h"
#include "../gameobjects/Entrance.h"
#include "../gameobjects/lemmings/LemmingsHandler.h"

namespace Lemmings::Scene {
    Level::Level(const std::string& levelName) : levelName_(levelName)
    {
        
    }

    std::shared_ptr<LevelData> Level::parseLevel()
    {
        std::ifstream file(ASSETS_PATH"levels/" + this->levelName_ + ".lvl");

        if (!file.is_open())
            throw std::runtime_error("Couldn't open level file: " + this->levelName_);

        std::string line;
        int index = 0;
        std::shared_ptr<LevelData> data = std::make_shared<LevelData>();

        auto errorCheckStringToInt = [](const std::string& input, const char* endPtr)
        {
            if (endPtr == input.c_str()) {
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
        };
        
        char* endPtr;
        while (std::getline(file, line))
        {
            switch (index)
            {
            case 0:
                data->levelNum = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            case 1:
                data->name = line;
                break;
            case 2:
                data->image = line;
                break;
            case 3:
                data->timeLimit = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            case 4:
                data->saveRequirement = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            case 5:
                data->amountOfLemmings = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
            case 6:
                data->releaseRate = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
            case 7: { // New case for the last line
                    std::stringstream ss(line);
                    std::string token;
                    std::vector fields = {
                        &data->climbers,
                        &data->floaters,
                        &data->bombers,
                        &data->blockers,
                        &data->builders,
                        &data->bashers,
                        &data->miners,
                        &data->diggers
                    };

                    int fieldIndex = 0;
                    while (std::getline(ss, token, ',')) {
                        if (fieldIndex < fields.size()) {
                            *fields[fieldIndex] = std::strtol(token.c_str(), &endPtr, 10);
                            errorCheckStringToInt(token, endPtr);
                            fieldIndex++;
                        } else {
                            throw std::runtime_error("Too many values in the last line.");
                        }
                    }
                    break;
            }
            default:
                throw std::runtime_error("Unexpected line index: " + std::to_string(index));
            }

            index++;
        }

        return data;
    }

    void Level::init()
    {
        std::shared_ptr<LevelData> data = this->parseLevel();
        
        const auto map = std::make_shared<Map>(ASSETS_PATH + data->image);
        const auto lemmingHandler = std::make_shared<LemmingsHandler>(map);
        const auto camera = std::make_shared<Camera>();
        const auto ui = std::make_shared<GameUI>(camera, data);
        const auto entrance = std::make_shared<Entrance>(ui, sf::Vector2i(200.0f, 29.0f), lemmingHandler.get(), data->releaseRate);
        const auto cursor = std::make_shared<Cursor>(lemmingHandler, camera, ui);
        
        // lemmingHandler->addLemming({225, 29});
        // lemmingHandler->addLemming({315, 50});
        
        this->addGameObject(camera);
        this->addGameObject(map);
        this->addGameObject(entrance);
        this->addGameObject(lemmingHandler);
        this->addGameObject(ui);
        this->addGameObject(cursor);
        
        IScene::init();
        
        camera->activate();
        camera->setPosition({69, 0});
    }

    void Level::update(float delta)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            Engine::Core::Instance()->getWindow()->close();
            return;
        }
        
        IScene::update(delta);
    }

    void Level::draw(sf::RenderTarget& renderTarget)
    {
        IScene::draw(renderTarget);
    }

    void Level::destroy()
    {
        Lemming::destroyTextures();
        UI::NumericSprite::destroyTextures();
    }
} // Lemmings