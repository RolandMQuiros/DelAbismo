#include "TestState.h"
#include <iostream>
#include <sstream>

namespace test {

TestState::TestState(da::Game &game) :
mGame(game) {
    mDebugDisplay.setString("Press [0:9] to specify return code and exit");
    mDebugDisplay.setCharacterSize(12);
    mFpsDisplay.setCharacterSize(12);
    mFpsDisplay.setPosition(0.f, 12.f);
    
    mExitCodes[0] = sf::Keyboard::Num0;
    mExitCodes[1] = sf::Keyboard::Num1;
    mExitCodes[2] = sf::Keyboard::Num2;
    mExitCodes[3] = sf::Keyboard::Num3;
    mExitCodes[4] = sf::Keyboard::Num4;
    mExitCodes[5] = sf::Keyboard::Num5;
    mExitCodes[6] = sf::Keyboard::Num6;
    mExitCodes[7] = sf::Keyboard::Num7;
    mExitCodes[8] = sf::Keyboard::Num8;
    mExitCodes[9] = sf::Keyboard::Num9;
}

void TestState::update() {
    for (unsigned int i = 0; i < 9; i++) {
        if (sf::Keyboard::isKeyPressed(mExitCodes[i])) {
            throw i;
        }
    }
    
    for (unsigned int i = 0; i < mBehaviors.size(); i++) {
        if (mBehaviors[i]) {
            mBehaviors[i]->update(mGame.getFrameTime());
        }
    }
    
    for (unsigned int i = 0; i < mUpdaters.size(); i++) {
        mUpdaters[i](mGame, mGame.getFrameTime());
    }
    
    mFpsCounter += mGame.getFrameTime();
    if (mFpsCounter.asSeconds() > 1.f) {
        mFpsCounter = sf::Time::Zero;
        
        std::stringstream ss;
        ss << "FPS: " << (1.f / mGame.getFrameTime().asSeconds()) << std::endl;
        
        mFpsDisplay.setString(ss.str());
    }
}

void TestState::draw() {
    mGame.clear();
    
    for (unsigned int i = 0; i < mRenderBehaviors.size(); i++) {
        if (mRenderBehaviors[i]) {
            mRenderBehaviors[i]->update(mGame.getFrameTime());
        }
    }
    
    for (unsigned int i = 0; i < mRenderers.size(); i++) {
        mRenderers[i](mGame, sf::RenderStates());
    }
    
    mGame.draw(mDebugDisplay);
    mGame.draw(mFpsDisplay);
}

da::EntityPtr TestState::createEntity() {
    return mEntities.create();
}

void TestState::refreshEntity(const da::EntityPtr &entity) {
    mEntities.refresh(entity);
}

void TestState::refreshEntity(const da::EntityRef &entity) {
    mEntities.refresh(entity);
}

void TestState::addBehavior(const da::BehaviorPtr &behavior, bool renderer) {
    if (behavior) {
        if (renderer) {
            mRenderBehaviors.push_back(behavior);
        } else {
            mBehaviors.push_back(behavior);
        }
        
        mEntities.addBehavior(behavior);
    }
}

void TestState::addBehavior(da::Behavior *behavior, bool renderer) {
    if (behavior != NULL) {
        addBehavior(da::BehaviorPtr(behavior), renderer);
    }
}

void TestState::addUpdater(Updater &updater) {
    mUpdaters.push_back(updater);
}

void TestState::addRenderer(Renderer &renderer) {
    mRenderers.push_back(renderer);
}

}
