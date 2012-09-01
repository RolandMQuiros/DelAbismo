#include "EntityEnvironment.h"

namespace test {

EntityEnvironment::EntityEnvironment() :
Game(sf::VideoMode(640, 480), "Del Abismo Entity Test Environment") {
    
}

void EntityEnvironment::SetUp() {
    State = new TestState(Game);
    Game.pushState(State);
}

void EntityEnvironment::TearDown() {
    
}
    
}
