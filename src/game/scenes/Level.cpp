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
#include "../gameobjects/Exit.h"
#include "../gameobjects/lemmings/LemmingsHandler.h"

namespace Lemmings::Scene {
    Level::Level(const std::string& levelName) : levelName_(levelName)
    {
        
    }

    std::unique_ptr<LevelData> Level::parseLevel() const
    {
        std::ifstream file(this->levelName_);

        if (!file.is_open())
            throw std::runtime_error("Couldn't open level file: " + this->levelName_);

        std::string line;
        int index = 0;
        std::unique_ptr<LevelData> data = std::make_unique<LevelData>();

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
                data->dirtIndex = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
            case 4:
                data->exitIndex = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
            case 5:
                data->timeLimit = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            case 6:
                data->saveRequirement = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            case 7:
                data->amountOfLemmings = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            case 8:
                data->releaseRate = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            case 9: { // New case for the last line
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
            case 10: {
                data->spawnX = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            }
            case 11: {
                data->spawnY = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            }
            case 12: {
                data->exitX = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            }
            case 13: {
                data->exitY = std::strtol(line.c_str(), &endPtr, 10);
                errorCheckStringToInt(line, endPtr);
                break;
            }
            case 14: {
                    data->cameraX = std::strtol(line.c_str(), &endPtr, 10);
                    errorCheckStringToInt(line, endPtr);
                    break;
            }
            case 15: {
                    data->cameraY = std::strtol(line.c_str(), &endPtr, 10);
                    errorCheckStringToInt(line, endPtr);
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
        this->levelData_ = this->parseLevel();
        
        auto map = std::make_unique<Map>(ASSETS_PATH + this->levelData_->image);
        auto lemmingHandler = std::make_unique<LemmingsHandler>(map.get(), this->levelData_.get());
        auto camera = std::make_unique<Camera>();
        auto ui = std::make_unique<GameUI>(this->levelData_.get());
        auto entrance = std::make_unique<Entrance>(sf::Vector2i(this->levelData_->spawnX, this->levelData_->spawnY), lemmingHandler.get(), this->levelData_->releaseRate, this->levelData_->amountOfLemmings);
        auto exit = std::make_unique<Exit>(this->levelData_.get());
        auto cursor = std::make_unique<Cursor>(lemmingHandler.get(), camera.get(), ui.get());
        
        this->entrance_ = entrance.get();
        this->lemmingHandler_ = lemmingHandler.get();
        Camera* cam = camera.get();
        
        this->addGameObject(std::move(camera));
        this->addGameObject(std::move(map));
        this->addGameObject(std::move(entrance));
        this->addGameObject(std::move(exit));
        this->addGameObject(std::move(lemmingHandler));
        this->addGameObject(std::move(ui));
        this->addGameObject(std::move(cursor));
        
        IScene::init();
        
        cam->activate();
        cam->setPosition(sf::Vector2f(this->levelData_->cameraX, this->levelData_->cameraY));
    }

    void Level::update(float delta)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            Engine::Core::Instance()->getWindow()->close();
            return;
        }

        if (this->entrance_->getAmountOut() > 0 && this->lemmingHandler_->getAmountOfLemmings() == 0)
        {
            Engine::Core::Instance()->removeCurrentScene();
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
    }
} // Lemmings