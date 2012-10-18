cmake_minimum_required(VERSION 2.6)
project(delabismo)

include_directories(include)
link_libraries(sfml-graphics sfml-audio sfml-window sfml-system)
add_definitions(-std=c++0x)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(da_sources      
    src/da/Attribute.cpp
    src/da/Behavior.cpp
    src/da/ContentManager.cpp
    src/da/DAException.cpp
    src/da/Entity.cpp
    src/da/EntityBehavior.cpp
    src/da/EntityManager.cpp
    src/da/Game.cpp
    src/da/MathHelper.cpp
    src/da/RenderBehavior.cpp
    src/da/StringHelper.cpp
    src/da/XmlHelper.cpp
)
    
set(twod_sources
    src/da/twod/Animation.cpp
    src/da/twod/MapReader.cpp
    src/da/twod/Spatial.cpp
    src/da/twod/TileRect.cpp
    src/da/twod/TileSet.cpp
    
    src/da/twod/attr/Depth.cpp
    src/da/twod/bhvr/SpatialRenderer.cpp
)

add_library(delabismo SHARED ${da_sources})

add_library(delabismo-2d SHARED ${twod_sources})
target_link_libraries(delabismo-2d delabismo)
