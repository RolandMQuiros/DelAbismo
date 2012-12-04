#include "da/EntityBehavior.h"

namespace da {

EntityBehavior::~EntityBehavior() {

}

void EntityBehavior::updateEntities(EntityGroup &entities) {
    beginUpdate(entities);
    for (EntityGroup::iterator iter = entities.begin();
         iter != entities.end(); iter++) {
        if (iter->expired()) {
            removeEntity(*iter);
        } else {
            updateEntity(iter->lock());
        }
    }
    endUpdate(entities);
}

void EntityBehavior::beginUpdate(EntityGroup &entities) {
    
}

void EntityBehavior::endUpdate(EntityGroup &entities) {
}

}
