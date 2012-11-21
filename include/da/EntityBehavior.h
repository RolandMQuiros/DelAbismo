#ifndef DA_ENTITYBEHAVIOR_H
#define DA_ENTITYBEHAVIOR_H

#include "da/Behavior.h"

namespace da {

class EntityBehavior : public da::Behavior {
public:
    virtual ~EntityBehavior();

protected:
    virtual void updateEntities(EntityGroup &entities);
    
    virtual void begin(EntityGroup &entities);
    virtual void updateEntity(const EntityPtr &entity)=0;
    virtual void end(EntityGroup &entities);
};

}

#endif
