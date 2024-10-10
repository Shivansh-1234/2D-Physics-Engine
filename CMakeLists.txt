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
        src/Physics/Shapes/BoxShape.h
        src/Physics/Collisions/Collision.cpp
        src/Physics/Collisions/Collision.h
        src/Physics/Collisions/CollisionInformation.cpp
        src/Physics/Collisions/CollisionInformation.h
        src/Physics/Collisions/CollisionResolver.cpp
        src/Physics/Collisions/CollisionResolver.h)

# --- PLATFORM DETECTION ---
if(WIN32)
    message(STATUS "Configuring for Windows")

    # --- SDL2 Setup for Windows ---
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
    set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})

    # Link SDL2 and SDL2_image
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

elseif(UNIX)
    message(STATUS "Configuring for Linux")

    # --- SDL2 Setup for Linux ---
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    # Find SDL2_image
    find_package(SDL2_image REQUIRED)
    include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

    # Link SDL2 and SDL2_image
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_image::SDL2_image)

endif()
