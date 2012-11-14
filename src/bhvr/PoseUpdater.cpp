#include <cmath>

#include <da/MathHelper.h>

#include "attr/Actor.h"
#include "attr/Poses.h"
#include "attr/Sprite.h"

#include "bhvr/PoseUpdater.h"

#include "CardinalDirection.h"

namespace bhvr {

bool PoseUpdater::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<attr::Poses>() &&
           entity.hasAttribute<attr::Sprite>();
}

void PoseUpdater::updateEntity(const da::EntityPtr &entity) {
    // Get attribute references
    attr::Poses &poses = entity->getAttribute<attr::Poses>();
    
    // Early out if disabled
    if (!poses.isEnabled) {
        return;
    }
    attr::Sprite &sprite = entity->getAttribute<attr::Sprite>();
    
    // Update animation
    poses.time += getDelta();
    if (poses.time > poses.timePerFrame) {
        poses.time = sf::Time::Zero;
        
        if (!poses.nextFrame()) {
            finished(entity);
        }
    }
    
    // Apply to sprite
    Pose::Frame frame = poses.getFrame();
    
    sprite.setTextureRect(frame.rect);
    sprite.setOrigin(frame.origin);
}

}
