#include <cmath>

#include <da/twod/attr/Transform.h>

#include "attr/MotionQueue.h"
#include "bhvr/MotionMover.h"

namespace bhvr {

bool MotionMover::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::attr::Transform>() &&
           entity.hasAttribute<attr::MotionQueue>();
}

void MotionMover::updateEntities(da::EntityGroup &entities) {
    da::EntityGroup::iterator iter;
    for (iter = entities.begin(); iter != entities.end(); iter++) {
        if (moveEntity(*iter->lock())) {
            emptyQueueHandler(*iter);
        }
    }
}

bool MotionMover::moveEntity(da::Entity &entity) {
    attr::MotionQueue &queue = entity.getAttribute<attr::MotionQueue>();
    
    // Early out
    if (queue.motions.empty()) {
        return true;
    }
    
    attr::MotionQueue::Motion &motion = queue.motions.front();
    da::attr::Transform &xform = entity.getAttribute<da::attr::Transform>();
    
    // Get distances    
    float dp = getDelta().asSeconds() * motion.speed;
    float dx = dp * cos(motion.direction);
    float dy = dp * sin(motion.direction);
    
    // Move the person
    xform.move(dx, dy);
    motion.distance -= dp;
    
    // Move onto the next motion
    if (motion.distance <= 0.f) {
        queue.motions.pop();
    }
    
    return false;
}

}