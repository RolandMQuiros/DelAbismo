#ifndef TEST_TESTSTATE_H
#define TEST_TESTSTATE_H

#include <functional>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "da/Behavior.h"
#include "da/Game.h"
#include "da/State.h"
#include "da/EntityManager.h"

namespace test {

class TestState : public da::State {
public:
    typedef std::function<void (da::Game &game, const sf::Time &)> Updater;
    typedef std::function<void (sf::RenderTarget &target,
                                sf::RenderStates states)> Renderer;
    
    TestState(da::Game &game);
    void update();
    void draw();
    
    da::EntityPtr createEntity();
    void refreshEntity(const da::EntityPtr &entity);
    void refreshEntity(const da::EntityRef &entity);
    
    void addBehavior(const da::BehaviorPtr &behavior, bool renderer=false);
    void addBehavior(da::Behavior *behavior, bool renderer=false);
    
    void addUpdater(Updater &updater);
    void addRenderer(Renderer &renderer);
    
private:
    da::Game &mGame;
    da::EntityManager mEntities;
    
    sf::Text mDebugDisplay;
    sf::Keyboard::Key mExitCodes[10];
    
    std::vector<da::BehaviorPtr> mBehaviors;
    std::vector<da::BehaviorPtr> mRenderBehaviors;
    
    sf::Time mFpsCounter;
    sf::Text mFpsDisplay;
    
    std::vector<Updater> mUpdaters;
    std::vector<Renderer> mRenderers;
};

}

#endif
