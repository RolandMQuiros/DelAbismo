#include "da/Behavior.h"

namespace da {

Behavior::Behavior() :
mIsActive(true) {
    
}

Behavior::~Behavior() {
    
}
    
void Behavior::setActive(bool active) {
    mIsActive = active;
}

bool Behavior::isActive() const {
    return mIsActive;
}

void Behavior::refreshEntity(const EntityRef &entity) {
    // Make sure we're not pointing to a dead object
    if (entity.expired()) {
        return;
    }
    
    // Check if the entity already exists in the active list
    bool contains = mActive.find(entity) != mActive.end();
    
    // Check if the entity is compatible
    bool compatible = isCompatible(*entity.lock());
    
    if (contains && !compatible) {
        mRemoved.push(entity);
        removedEntity(entity);
    } else if (!contains && compatible) {
        mAdded.push(entity);
        addedEntity(entity);
    }
}

void Behavior::initialize() {
    // Put initialization code here
}

void Behavior::dispose() {
    // Put disposal code here
}

void Behavior::update(const sf::Time &deltaTime) {
    // Add entities to the active list
    while (!mAdded.empty()) {
        if (mAdded.front().expired()) {
            mAdded.pop();
            continue;
        }
        
        mActive.insert(mAdded.front());
        mAdded.pop();
    }
    
    // Remove entities from the active list
    while (!mRemoved.empty()) {
        EntityGroup::iterator search = mActive.find(mRemoved.front());
        if (search != mActive.end()) {
            mActive.erase(search);
        }
        mRemoved.pop();
    }
    
    mDelta = deltaTime;
    
    if (mIsActive) {
        updateEntities(mActive);
    }
}

const sf::Time &Behavior::getDelta() const {
    return mDelta;
}

void Behavior::addEntity(const EntityRef &entity) {
    if (!entity.expired()) {
        mAdded.push(entity);
    }
}

void Behavior::removeEntity(const EntityRef &entity) {
    mRemoved.push(entity);
}

void Behavior::addedEntity(const EntityRef &entity) {
    
}

void Behavior::removedEntity(const EntityRef &entity) {
    
}

}
