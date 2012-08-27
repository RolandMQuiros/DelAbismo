#ifndef TEST_ENTITYENVIRONMENT_H
#define TEST_ENTITYENVIRONMENT_H

#include <gtest/gtest.h>
#include "da/Game.h"
#include "TestState.h"

namespace test {

class EntityEnvironment : public ::testing::Test {
protected:
    EntityEnvironment();
    void SetUp();
    void TearDown();
    
    da::Game Game;
    TestState *State;
};

}

#endif
