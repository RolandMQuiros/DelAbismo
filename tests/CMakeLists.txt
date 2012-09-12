cmake_minimum_required(VERSION 2.6)
project(delabismo-test)

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++0x)

include_directories(${CMAKE_BINARY_DIR}/../include)

link_directories(${CMAKE_BINARY_DIR}/../lib)

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

add_definitions(-std=c++0x)
set(CMAKE_BUILD_TYPE Debug)

set(sources 
    TestState.cpp
    EntityEnvironment.cpp
)

add_executable(SpatialTest ${sources} SpatialTest.cpp)

set(keyboard_test_sources
    ../src/marked/KeyboardInput.cpp
    KeyboardTest.cpp
)    
add_executable(KeyboardTest ${keyboard_test_sources})