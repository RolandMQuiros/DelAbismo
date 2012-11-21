#include "da/EntityBehavior.h"

namespace da {

EntityBehavior::~EntityBehavior() {

}

void EntityBehavior::updateEntities(EntityGroup &entities) {
    begin(entities);
    for (EntityGroup::iterator iter = entities.begin();
         iter != entities.end(); iter++) {
        if (iter->expired()) {
            removeEntity(*iter);
        } else {
            updateEntity(iter->lock());
        }
    }
    end(entities);
}

void EntityBehavior::begin(EntityGroup &entities) {
    
}

void EntityBehavior::end(EntityGroup &entities) {
}

}
