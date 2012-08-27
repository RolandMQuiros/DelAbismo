#include "da/Behavior.h"

namespace da {

Behavior::Behavior() :
mvIsActive(true) {
    
}

Behavior::~Behavior() {
    
}
    
void Behavior::setActive(bool active) {
    mvIsActive = active;
}

bool Behavior::isActive() const {
    return mvIsActive;
}

void Behavior::refreshEntity(const EntityRef &entity) {
    if (entity.expired()) {
        return;
    }
    
    bool contains = mvActive.find(entity) != mvActive.end();
    bool compatible = isCompatible(*entity.lock());
    
    if (contains && !compatible) {
        mvRemoved.push(entity);
        removedEntity(entity);
    } else if (!contains && compatible) {
        mvAdded.push(entity);
        addedEntity(entity);
    }
}

void Behavior::initialize() {
    
}

void Behavior::dispose() {
    
}

void Behavior::update(const sf::Time &deltaTime) {
    while (!mvAdded.empty()) {
        if (mvAdded.front().expired()) {
            mvAdded.pop();
            continue;
        }
        
        mvActive.insert(mvAdded.front());
        mvAdded.pop();
    }
    
    while (!mvRemoved.empty()) {
        EntityGroup::iterator search = mvActive.find(mvRemoved.front());
        if (search != mvActive.end()) {
            mvActive.erase(search);
        }
        mvRemoved.pop();
    }
    
    mvDelta = deltaTime;
    
    if (mvIsActive) {
        updateEntities(mvActive);
    }
}

const sf::Time &Behavior::getDelta() const {
    return mvDelta;
}

void Behavior::addEntity(const EntityRef &entity) {
    if (!entity.expired()) {
        mvAdded.push(entity);
    }
}

void Behavior::removeEntity(const EntityRef &entity) {
    mvRemoved.push(entity);
}

void Behavior::cleanEntities() {
    while (!mvAdded.empty()) {
        if (mvAdded.front().expired()) {
            mvAdded.pop();
            continue;
        }
        
        mvActive.insert(mvAdded.front());
        mvAdded.pop();
    }
    
    while (!mvRemoved.empty()) {
        EntityGroup::iterator search = mvActive.find(mvRemoved.front());
        if (search != mvActive.end()) {
            mvActive.erase(search);
        }
        mvRemoved.pop();
    }
}

bool Behavior::isCompatible(const Entity &entity) const {
    return false;
}

void Behavior::addedEntity(const EntityRef &entity) {
    
}

void Behavior::removedEntity(const EntityRef &entity) {
    
}

}
