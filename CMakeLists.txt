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
        src/game/Map.cpp
        src/game/Map.h
        src/game/Node.cpp
        src/game/Node.h
        src/engine/GameObject.h
        src/game/lemmings/Lemming.cpp
        src/game/lemmings/Lemming.h
        src/game/lemmings/states/Walker.cpp
        src/game/lemmings/states/Walker.h
        src/engine/Timer.cpp
        src/engine/Timer.h
        src/game/lemmings/states/Faller.cpp
        src/game/lemmings/states/Faller.h
        src/engine/AnimatedTexture.cpp
        src/engine/AnimatedTexture.h
        src/game/lemmings/LemmingsHandler.cpp
        src/game/lemmings/LemmingsHandler.h
        src/game/Camera.cpp
        src/game/Camera.h
        src/game/lemmings/states/Digger.cpp
        src/game/lemmings/states/Digger.h
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
