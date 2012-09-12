cmake_minimum_required(VERSION 2.6)
project(delabismo-test)

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++0x)

include_directories(${CMAKE_BINARY_DIR}/../../include
                    ${CMAKE_BINARY_DIR}/..)

link_directories(${CMAKE_BINARY_DIR}/../../lib)

link_libraries( 
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
    
    delabismo 
    delabismo-2d
    
    gtest 
    pthread
)

add_definitions(-std=c++0x -pg)
set(CMAKE_BUILD_TYPE Debug)

set(sources 
    ../../src/bhvr/DirectedAnimation.cpp
    ../TestState.cpp
    ../EntityEnvironment.cpp
)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pg" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pg" )

add_executable(DirectedAnimationTest ${sources} DirectedAnimationTest.cpp)
