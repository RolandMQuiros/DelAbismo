#include <cmath>

#include <da/twod/attr/Transform.h>
#include <da/MathHelper.h>

#include "attr/Person.h"
#include "attr/Poses.h"
#include "attr/Sprite.h"

#include "bhvr/Walker.h"


#define DELTA_THRESH 0.002f
#define NUM_SLICES 8 // Number of unique directions we want to render

namespace bhvr {

bool Walker::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::attr::Transform>() &&
           entity.hasAttribute<attr::Person>() &&
           entity.hasAttribute<attr::Poses>() &&
           entity.hasAttribute<attr::Sprite>();
}

void Walker::updateEntity(const da::EntityPtr &entity) {
    // Get attributes
    da::attr::Transform &xform = entity->getAttribute<da::attr::Transform>();
    attr::Poses &poses = entity->getAttribute<attr::Poses>();
    attr::Sprite &sprite = entity->getAttribute<attr::Sprite>();
    sf::Vector2f &prevPos =
        entity->getAttribute<attr::Person>().previousPosition;
    
    // Make sure they're enabled.  Early out if they're not.
    if (!poses.isEnabled || ! sprite.isEnabled()) {
        return;
    }
    
    // Get change in position
    sf::Vector2f deltaPos = prevPos - xform.getPosition();
    float distance = da::MathHelper::length(deltaPos.x, deltaPos.y);
    
    // Don't bother if the distance is too small.  We may regret this on the
    // magical computers of tomorrow (or if we forget to limit the framerate)
    if (distance < DELTA_THRESH) {
        return;
    }
    
    // Calculate the angle of movement.  Remember, atan2 yields [-pi, +pi].
    float angle = atan2(deltaPos.y, deltaPos.x);
    
    // Calculate which eighth of the 360 degree pie our entity is moving in.
    // This will yield a number in the range [-NUM_SLICES/2, +NUM_SLICES/2]
    int region = (angle / da::MathHelper::TwoPi) * NUM_SLICES;
    
    // Correlate the region to direction
    CardinalDirection direction = (CardinalDirection)(region + NUM_SLICES/2);
    
    // Set the appropriate pose
    poses.setCurrentFrame(directionToString(direction), 
}

}
