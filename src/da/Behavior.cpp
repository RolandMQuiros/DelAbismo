#include "da/Behavior.h"

namespace da {

Behavior::Behavior() :
mvIsActive(true) {
    
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
    
    EntityPtr entPtr = entity.lock();
    SearchIter search = mvSearchList.find(entPtr->getId());
    bool contains = search != mvSearchList.end();
    bool compatible = isCompatible(*entity.lock());
    
    if (contains && !compatible) {
        mvRemoved.push(search->second);
    } else if (!contains && compatible) {
        mvAdded.push(entity);
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
        
        EntityPtr added = mvAdded.front().lock();
        
        unsigned int id = added->getId();
        
        mvActiveEntities.push_back(mvAdded.front());
        mvActiveIds.push_back(id);
        mvSearchList[mvActiveEntities.size() - 1] = id;
        
        mvAdded.pop();
    }
    
    while (!mvRemoved.empty()) {
        unsigned int index = mvRemoved.front();
        
        mvActiveEntities.erase(mvActiveEntities.begin() + index);
        mvSearchList.erase(mvActiveIds[index]);
        mvActiveIds.erase(mvActiveIds.begin() + index);
        
        mvRemoved.pop();
    }
    
    if (mvIsActive) {
        for (unsigned int i = 0; i < mvActiveEntities.size(); i++) {
            EntityRef &entity = mvActiveEntities[i];
            if (entity.expired()) {
                mvRemoved.push(i);
            } else {
                updateEntity(deltaTime, *entity.lock());
            }
        }
    }
}

bool Behavior::isCompatible(const Entity &entity) const {
    return false;
}

void Behavior::updateEntity(const sf::Time &deltaTime, Entity &entity) {
    
}
    
}
