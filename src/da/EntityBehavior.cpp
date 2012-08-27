#include "da/EntityBehavior.h"

namespace da {

EntityBehavior::~EntityBehavior() {

}

void EntityBehavior::updateEntities(EntityGroup &entities) {
    begin();
    for (EntityGroup::iterator iter = entities.begin();
         iter != entities.end(); iter++) {
        if (iter->expired()) {
            removeEntity(*iter);
        } else {
            updateEntity(*iter->lock());
        }
    }
    end();
}

void EntityBehavior::begin() {
    
}

void EntityBehavior::end() {
}

}
