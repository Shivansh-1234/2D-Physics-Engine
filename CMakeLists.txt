cmake_minimum_required(VERSION 3.22)
project(2D_PHYSICS_ENGINE)

set(CMAKE_CXX_STANDARD 14)

# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
add_executable(${PROJECT_NAME} src/main.cpp
        src/Physics/Particle.cpp
        src/Physics/Vec2.cpp
        src/Application.cpp
        src/Graphics.cpp
        lib/SDL2_gfx/SDL2_gfxPrimitives.c
        lib/SDL2_gfx/SDL2_imageFilter.c
        lib/SDL2_gfx/SDL2_rotozoom.c)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})