#ifndef DA_ENTITYBEHAVIOR_H
#define DA_ENTITYBEHAVIOR_H

#include "da/Behavior.h"

namespace da {

class EntityBehavior : public da::Behavior {
public:
    virtual ~EntityBehavior();

protected:
    void updateEntities(EntityGroup &entities);
    
    virtual void begin();
    virtual void updateEntity(Entity &entity)=0;
    virtual void end();
};

}

#endif
