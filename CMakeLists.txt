cmake_minimum_required(VERSION 2.6)
project(delabismo)
include_directories(include)
link_libraries(sfml-graphics sfml-audio sfml-window sfml-system)
add_definitions(-std=c++0x)
set(CMAKE_BUILD_TYPE Debug)

set(sources src/da/Animation.cpp
            src/da/Attribute.cpp
            src/da/Behavior.cpp
            src/da/ContentManager.cpp
            src/da/DAException.cpp
            src/da/Depth.cpp
            src/da/DepthDrawList.cpp
            src/da/DepthRenderBehavior.cpp
            src/da/Entity.cpp
            src/da/EntityManager.cpp
            src/da/Game.cpp
            src/da/Helper.cpp
            src/da/MathHelper.cpp
            src/da/RenderBehavior.cpp
            src/da/TileRect.cpp
            src/da/TileSet.cpp
            src/da/Transform.cpp
            src/da/XmlHelper.cpp
            
            src/common/WalkSprite.cpp
            
            src/sim/CharacterRenderer.cpp
            src/sim/PlayerRenderer.cpp
            src/sim/PlayerUpdater.cpp
            src/sim/Sim.cpp
            
            src/main.cpp
    )

add_executable(delabismo ${sources})