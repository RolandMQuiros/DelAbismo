#ifndef DA_BEHAVIOR_H
#define DA_BEHAVIOR_H

#include <memory>
#include <unordered_set>
#include <queue>
#include <SFML/System/Time.hpp>

#include "da/Entity.h"

namespace da {

class Behavior {
public:
    Behavior();
    virtual ~Behavior();

    void setActive(bool active);
    bool isActive() const;

    void refreshEntity(const EntityRef &entity);

    virtual void initialize();
    virtual void dispose();
    
    void update(const sf::Time &deltaTime);
    
protected:
    const sf::Time &getDelta() const;

    void addEntity(const EntityRef &entity);
    void removeEntity(const EntityRef &entity);
    void cleanEntities();

    virtual bool isCompatible(const Entity &entity) const;

    virtual void addedEntity(const EntityRef &entity);
    virtual void removedEntity(const EntityRef &entity);
    
    virtual void updateEntities(EntityGroup &entities)=0;
private:
    bool mvIsActive;
    unsigned long mvDependencies;
    sf::Time mvDelta;
    
    EntityGroup mvActive;
    std::queue<EntityRef> mvAdded;
    std::queue<EntityRef> mvRemoved;

};
typedef std::shared_ptr<Behavior> BehaviorPtr;
typedef std::weak_ptr<Behavior> BehaviorRef;

}

#endif
