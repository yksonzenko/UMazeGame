cmake_minimum_required(VERSION 3.18.2)

set(PROJECT_NAME maze)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

add_subdirectory(engine)
add_subdirectory(game)
