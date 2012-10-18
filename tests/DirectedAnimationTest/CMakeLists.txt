cmake_minimum_required(VERSION 2.6)
project(delabismo-test)

set(CMAKE_BUILD_TYPE Debug)
add_definitions(-std=c++0x)

include_directories(${CMAKE_BINARY_DIR}/../../include
                    ${CMAKE_BINARY_DIR}/..)

link_directories(${CMAKE_BINARY_DIR}/../../lib)

# Windows
# include_directories(D:/Libraries/gtest/include)
# link_directories(D:/Libraries/gtest)

# Remove pthreads support from Windows gtest
# set(GTEST_HAS_PTHREAD 0)

# Print included directories
# get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
# message("include directories = ${inc_dirs}")

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
    ../../src/attr/DirectedAnimation.cpp
    ../../src/bhvr/DirectedAnimation.cpp
    ../TestState.cpp
    ../EntityEnvironment.cpp
)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pg" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pg" )

add_executable(DirectedAnimationTest ${sources} DirectedAnimationTest.cpp)
add_executable(AnimationTest AnimationTest.cpp)
