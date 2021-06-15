# Game

cmake_minimum_required(VERSION 3.18.2)

add_subdirectory(src)

set(Game
    src/Game/Game.cpp
    src/Game/Game.hpp
)

set(Menu
    src/Menu/Menu.cpp
    src/Menu/Menu.hpp
)

set(Levels
    src/Levels/FirstLevel.cpp
    src/Levels/FirstLevel.hpp
    "src/Levels/SecondLevel.cpp"
    "src/Levels/SecondLevel.hpp"
)

set(Pacman
    src/Pacman/Pacman.cpp
    src/Pacman/Pacman.hpp
)

set(Ghosts
    src/Ghosts/RedBlinky.cpp
    src/Ghosts/RedBlinky.hpp
    "src/Ghosts/PinkPinky.cpp"
    "src/Ghosts/PinkPinky.hpp"
)

set(Map
    src/Map/Map.cpp
    src/Map/Map.hpp
)

set(Pathfinder
    src/Pathfinder/AStar.cpp
    src/Pathfinder/AStar.hpp
)

set(Score
    src/Score/Score.cpp
    src/Score/Score.hpp
)

set(GameHUDView
    "src/GameHUDView/GameHUDView.hpp"
    "src/GameHUDView/GameHUDView.cpp"
)

source_group("Source files" FILES ${Game} ${Menu} ${Levels} ${Pacman} ${Ghosts} ${Map} ${Pathfinder} ${Score} ${GameHUDView})


#Set app icon
if (APPLE)
    set(MACOSX_BUNDLE_ICON_FILE pacman_main_macos.icns)
    set(APP_ICON_MACOSX "${CMAKE_SOURCE_DIR}/assets/images/pacman_main_macos.icns")
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE main.cpp ${APP_ICON_MACOSX} 
                ${Game} ${Menu} ${Levels} ${Pacman} ${Map} ${Ghosts} ${Pathfinder} ${Score} ${GameHUDView})
else()
    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/assets/images/pacman_icon.rc")

    add_executable(${PROJECT_NAME} main.cpp ${APP_ICON_RESOURCE} 
                ${Game} ${Menu} ${Levels} ${Pacman} ${Map} ${Ghosts} ${Pathfinder} ${Score} ${GameHUDView} )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PRIVATE MiniKit::MiniKit)
target_link_libraries(${PROJECT_NAME} PRIVATE Engine::Engine)
target_link_libraries(${PROJECT_NAME} PRIVATE ECS::ECS)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/game/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
