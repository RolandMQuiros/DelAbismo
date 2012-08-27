#ifndef TEST_TESTSTATE_H
#define TEST_TESTSTATE_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "da/Behavior.h"
#include "da/Game.h"
#include "da/State.h"
#include "da/EntityManager.h"

namespace test {

class TestState : public da::State {
public:
    TestState(da::Game &game);
    void update();
    void draw();
    
    da::EntityPtr createEntity();
    void refreshEntity(const da::EntityPtr &entity);
    void refreshEntity(const da::EntityRef &entity);
    
    void addBehavior(const da::BehaviorPtr &behavior, bool renderer=false);
    void addBehavior(da::Behavior *behavior, bool renderer=false);
    
private:
    da::Game &mvGame;
    da::EntityManager mvEntities;
    
    sf::Text mvDebugDisplay;
    sf::Keyboard::Key mvExitCodes[10];
    
    std::vector<da::BehaviorPtr> mvBehaviors;
    std::vector<da::BehaviorPtr> mvRenderBehaviors;
};

}

#endif
