cmake_minimum_required(VERSION 2.6)
project(delabismo)
include_directories(include)
link_libraries(sfml-graphics sfml-audio sfml-window sfml-system)
add_definitions(-std=c++0x)
set(CMAKE_BUILD_TYPE Debug)

set(da_sources  src/da/Animation.cpp
                src/da/Attribute.cpp
                src/da/Behavior.cpp
                src/da/ContentManager.cpp
                src/da/DAException.cpp
                src/da/Entity.cpp
                src/da/EntityBehavior.cpp
                src/da/EntityManager.cpp
                src/da/Game.cpp
                src/da/MapReader.cpp
                src/da/MathHelper.cpp
                src/da/RenderBehavior.cpp
                src/da/StringHelper.cpp
                src/da/TileRect.cpp
                src/da/TileSet.cpp
                src/da/XmlHelper.cpp
                
                src/attr/Depth.cpp
                src/bhvr/SpatialRenderer.cpp
                
                src/Spatial.cpp
    )

add_library(delabismo ${da_sources})