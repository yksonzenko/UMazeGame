# Game ECS

cmake_minimum_required (VERSION 3.18.2)

set(Systems
    ECS/Systems/RenderSystem.cpp
    ECS/Systems/RenderSystem.hpp
    ECS/Systems/MovementSystem.cpp
    ECS/Systems/MovementSystem.hpp
    ECS/Systems/ItemsCollectionSystem.cpp
    ECS/Systems/ItemsCollectionSystem.hpp
    ECS/Systems/CollisionSystem.cpp
    ECS/Systems/CollisionSystem.hpp
    ECS/Systems/AIMovementSystem.cpp
    ECS/Systems/AIMovementSystem.hpp
    "ECS/Systems/BehaviourSystem.cpp"
    "ECS/Systems/BehaviourSystem.hpp"
    "ECS/Systems/LevelControlSystem.cpp"
    "ECS/Systems/PlayerInputControlSystem.cpp"
    "ECS/Systems/PlayerInputControlSystem.hpp"
)

set(Events
    ECS/Events/CollectionEvent.hpp
    ECS/Events/CollisionEvent.hpp
    ECS/Events/TargetingEvent.hpp
    ECS/Events/BehaviourEvent.hpp
    "ECS/Events/LivesEvent.hpp"
    "ECS/Events/GameOverEvent.hpp"
)

set(Components
    ECS/Components/Transform.hpp
    ECS/Components/Animation.hpp
    ECS/Components/Movement.hpp
    ECS/Components/MapTileRenderer.hpp
    ECS/Components/Bonus.hpp
    ECS/Components/Collision.hpp
    ECS/Components/Score.hpp
    ECS/Components/Lives.hpp
    ECS/Components/AIMovement.hpp
    ECS/Components/TunnelPath.hpp
    "ECS/Components/AIBehaviourMode.hpp"
    "ECS/Components/PlayerBehaviourMode.hpp"
    "ECS/Components/Item.hpp"
    "ECS/Components/Score.hpp"
    "ECS/Components/Input.hpp"
)

add_library(EntityCS ${Systems} ${Events} ${Components})

target_include_directories(EntityCS PUBLIC ECS)
target_link_libraries(EntityCS PUBLIC entityx::entityx)
target_link_libraries(EntityCS PUBLIC MiniKit::MiniKit)
target_link_libraries(EntityCS PUBLIC tmxlite::tmxlite)
target_link_libraries(EntityCS PUBLIC Engine::Engine)

add_library(ECS::ECS ALIAS EntityCS)
