#ifndef BHVR_COLLISIONMANAGER_H
#define BHVR_COLLISIONMANAGER_H

#include <da/Behavior.h>

namespace bhvr {

class CollisionManager : public da::Behavior {
public:
    bool isCompatible(const da::Entity &entity) const;
    void updateEntities(EntityGroup &entities);
}

}

#endif
