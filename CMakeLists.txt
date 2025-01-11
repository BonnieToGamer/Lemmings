cmake_minimum_required(VERSION 3.28)
project(Lemmings LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        src/engine/Core.cpp
        src/engine/Core.h
        src/engine/SceneManager.cpp
        src/engine/SceneManager.h
        src/engine/IScene.h
        src/engine/IState.h
        src/engine/StateMachineManager.h
        src/game/scenes/Level.cpp
        src/game/scenes/Level.h
        src/engine/ModifiableTexture.cpp
        src/engine/ModifiableTexture.h
        src/game/gameobjects/Map.cpp
        src/game/gameobjects/Map.h
        src/game/gameobjects/Node.cpp
        src/game/gameobjects/Node.h
        src/engine/GameObject.cpp
        src/engine/GameObject.h
        src/game/gameobjects/lemmings/Lemming.cpp
        src/game/gameobjects/lemmings/Lemming.h
        src/game/gameobjects/lemmings/states/Walker.cpp
        src/game/gameobjects/lemmings/states/Walker.h
        src/engine/Timer.cpp
        src/engine/Timer.h
        src/game/gameobjects/lemmings/states/Faller.cpp
        src/game/gameobjects/lemmings/states/Faller.h
        src/game/gameobjects/lemmings/LemmingsHandler.cpp
        src/game/gameobjects/lemmings/LemmingsHandler.h
        src/game/gameobjects/Camera.cpp
        src/game/gameobjects/Camera.h
        src/game/gameobjects/lemmings/states/Digger.cpp
        src/game/gameobjects/lemmings/states/Digger.h
        src/game/gameobjects/Cursor.cpp
        src/game/gameobjects/Cursor.h
        src/engine/Event.h
        src/game/LevelData.h
        src/game/gameobjects/Entrance.cpp
        src/game/gameobjects/Entrance.h
        src/game/gameobjects/Exit.cpp
        src/game/gameobjects/Exit.h
        src/game/gameobjects/ui/ui_buttons/Button.cpp
        src/game/gameobjects/ui/ui_buttons/Button.h
        src/game/gameobjects/ui/ui_buttons/NumberButton.cpp
        src/game/gameobjects/ui/ui_buttons/NumberButton.h
        src/game/gameobjects/ui/ui_buttons/JobButton.cpp
        src/game/gameobjects/ui/ui_buttons/JobButton.h
        src/game/gameobjects/GameUI.cpp
        src/game/gameobjects/GameUI.h
        src/game/gameobjects/lemmings/states/Miner.cpp
        src/game/gameobjects/lemmings/states/Miner.h
        src/game/gameobjects/ui/NumericSprite.cpp
        src/game/gameobjects/ui/NumericSprite.h
        src/game/gameobjects/ui/TimeDisplay.cpp
        src/game/gameobjects/ui/TimeDisplay.h
        src/game/gameobjects/ui/LemmingInfoDisplay.cpp
        src/game/gameobjects/ui/LemmingInfoDisplay.h
        src/game/gameobjects/ui/UIButtonType.h
        src/game/gameobjects/ui/DualNumericSprite.cpp
        src/game/gameobjects/ui/DualNumericSprite.h
        src/engine/SpriteSheet.cpp
        src/engine/SpriteSheet.h
        src/engine/SpriteSheetAnimation.cpp
        src/engine/SpriteSheetAnimation.h
        src/engine/AnimationManager.h
        src/engine/asset/ContentManager.cpp
        src/engine/asset/ContentManager.h
        src/engine/asset/GameAsset.h
        src/engine/asset/TextureAsset.cpp
        src/engine/asset/TextureAsset.h
        src/game/gameobjects/lemmings/states/Winner.cpp
        src/game/gameobjects/lemmings/states/Winner.h
)
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)
target_compile_definitions(main PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/assets/")

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
