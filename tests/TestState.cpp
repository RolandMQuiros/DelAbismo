#include "TestState.h"
#include <iostream>

namespace test {

TestState::TestState(da::Game &game) :
mvGame(game) {
    mvDebugDisplay.setString("Press [0:9] to specify return code and exit");
    mvDebugDisplay.setCharacterSize(12);
    
    mvExitCodes[0] = sf::Keyboard::Num0;
    mvExitCodes[1] = sf::Keyboard::Num1;
    mvExitCodes[2] = sf::Keyboard::Num2;
    mvExitCodes[3] = sf::Keyboard::Num3;
    mvExitCodes[4] = sf::Keyboard::Num4;
    mvExitCodes[5] = sf::Keyboard::Num5;
    mvExitCodes[6] = sf::Keyboard::Num6;
    mvExitCodes[7] = sf::Keyboard::Num7;
    mvExitCodes[8] = sf::Keyboard::Num8;
    mvExitCodes[9] = sf::Keyboard::Num9;
}

void TestState::update() {
    for (unsigned int i = 0; i < 9; i++) {
        if (sf::Keyboard::isKeyPressed(mvExitCodes[i])) {
            throw i;
        }
    }
    
    for (unsigned int i = 0; i < mvBehaviors.size(); i++) {
        if (mvBehaviors[i]) {
            mvBehaviors[i]->update(mvGame.getFrameTime());
        }
    }
}

void TestState::draw() {
    mvGame.clear();
    
    for (unsigned int i = 0; i < mvRenderBehaviors.size(); i++) {
        if (mvRenderBehaviors[i]) {
            mvRenderBehaviors[i]->update(mvGame.getFrameTime());
        }
    }
    
    mvGame.draw(mvDebugDisplay);
}

da::EntityPtr TestState::createEntity() {
    return mvEntities.create();
}

void TestState::refreshEntity(const da::EntityPtr &entity) {
    mvEntities.refresh(entity);
}

void TestState::refreshEntity(const da::EntityRef &entity) {
    mvEntities.refresh(entity);
}

void TestState::addBehavior(const da::BehaviorPtr &behavior, bool renderer) {
    if (behavior) {
        if (renderer) {
            mvRenderBehaviors.push_back(behavior);
        } else {
            mvBehaviors.push_back(behavior);
        }
        
        mvEntities.addBehavior(behavior);
    }
}

void TestState::addBehavior(da::Behavior *behavior, bool renderer) {
    if (behavior != NULL) {
        addBehavior(da::BehaviorPtr(behavior), renderer);
    }
}

}
