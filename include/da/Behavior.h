#ifndef DA_BEHAVIOR_H
#define DA_BEHAVIOR_H

#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

#include <SFML/System/Time.hpp>

#include "da/Entity.h"

namespace da {

class Behavior {
public:
    Behavior();
    
    void setActive(bool active);
    bool isActive() const;
    
    void refreshEntity(const EntityRef &entity);
    
    virtual void initialize();
    virtual void dispose();
    
    void update(const sf::Time &deltaTime);
protected:
    virtual bool isCompatible(const Entity &entity) const;
    
    virtual void addedEntity(Entity &entity);
    virtual void removedEntity(Entity &entity);
    
    virtual void begin(const sf::Time &deltaTime);
    virtual void updateEntity(const sf::Time &deltaTime, Entity &entity);
    virtual void end(const sf::Time &deltaTime);
    
private:
    typedef std::unordered_map<unsigned int, unsigned int>::iterator SearchIter;
    
    bool mvIsActive;
    unsigned long mvDependencies;
    
    std::vector<EntityRef> mvActiveEntities;
    std::vector<unsigned int> mvActiveIds;
    std::unordered_map<unsigned int, unsigned int> mvSearchList;
    
    std::queue<EntityRef> mvAdded;
    std::queue<unsigned int> mvRemoved;
};

typedef std::shared_ptr<Behavior> BehaviorPtr;
typedef std::weak_ptr<Behavior> BehaviorRef;

}

#endif
