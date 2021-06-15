# Engine

cmake_minimum_required (VERSION 3.18.2)

project ("Engine")

add_subdirectory ("minikit")
add_subdirectory ("external")

set(FSMSources
    src/FSM/StateMachine.cc
    src/FSM/StateMachine.hh
)

set(World
    src/Engine/World/World.cpp
    src/Engine/World/World.hpp
)

set(InputManager
    src/Engine/InputManager/Buttons.cpp
    src/Engine/InputManager/Buttons.hpp
    src/Engine/InputManager/InputManager.cpp
    src/Engine/InputManager/InputManager.hpp
)

set(Scene
    src/Engine/Scene/Scene.cpp
    src/Engine/Scene/Scene.hpp
)

set(ViewPort
    src/Engine/ViewPort/ViewPort.cpp
    src/Engine/ViewPort/ViewPort.hpp
)

set(EntityComponent
    src/Engine/EntityComponent/Object.cpp
    src/Engine/EntityComponent/Object.hpp
    src/Engine/EntityComponent/Actor.cpp
    src/Engine/EntityComponent/Actor.hpp
    src/Engine/EntityComponent/Component.cpp
    src/Engine/EntityComponent/Component.hpp
)

set(Sprite
    src/Engine/Sprite/Sprite.cpp
    src/Engine/Sprite/Sprite.hpp
    src/Engine/Sprite/RectangleShape.cpp
    src/Engine/Sprite/RectangleShape.hpp
)

set(TextureManager
    src/Engine/TextureManager/TextureManager.cpp
    src/Engine/TextureManager/TextureManager.hpp
)

set(MapManager
    src/Engine/MapManager/MapManager.cpp
    src/Engine/MapManager/MapManager.hpp
)

set(Timer
    src/Engine/Timer/Timer.cpp
    src/Engine/Timer/Timer.hpp
)

add_library(Engine ${FSMSources} ${World} ${InputManager} ${Scene} ${ViewPort} ${EntityComponent} ${Sprite} ${TextureManager}
            ${MapManager} ${Timer}
)

target_include_directories(Engine PUBLIC src)
target_link_libraries(Engine PUBLIC MiniKit::MiniKit)
target_link_libraries(Engine PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(Engine PUBLIC tmxlite::tmxlite)
target_link_libraries(Engine PUBLIC glm::glm)
target_link_libraries(Engine PUBLIC entityx::entityx)

target_precompile_headers(Engine
    PRIVATE
        <cstdint>
        <iostream>
        <map>
        <memory>
        <string>
        <type_traits>
        <vector>
)

add_library(Engine::Engine ALIAS Engine)

# source_group("Source Files\\Engine" FILES ${EngineSources})
# source_group("Source Files\\FSM" FILES ${FSMSources})
