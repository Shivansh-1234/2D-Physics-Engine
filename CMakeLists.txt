cmake_minimum_required(VERSION 3.22)
project(2D_PHYSICS_ENGINE)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Physics/Body.cpp
        src/Physics/Vec2.cpp
        src/Application.cpp
        src/Graphics.cpp
        lib/SDL2_gfx/SDL2_gfxPrimitives.c
        lib/SDL2_gfx/SDL2_imageFilter.c
        lib/SDL2_gfx/SDL2_rotozoom.c
        src/Physics/Constants.h
        src/Physics/Force.cpp
        src/Physics/Force.h
        src/Physics/Math.cpp
        src/Physics/Math.h
        src/Physics/Shapes/Shape.cpp
        src/Physics/Shapes/Shape.h
        src/Physics/enums/ShapeType.h
        src/Physics/Shapes/CircleShape.cpp
        src/Physics/Shapes/CircleShape.h
        src/Physics/Shapes/PolygonShape.cpp
        src/Physics/Shapes/PolygonShape.h
        src/Physics/Shapes/BoxShape.cpp
        src/Physics/Shapes/BoxShape.h)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})