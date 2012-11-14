#include <cmath>

#include <da/twod/attr/Transform.h>
#include <da/MathHelper.h>

#include "attr/Person.h"
#include "attr/Poses.h"
#include "attr/Sprite.h"

#include "bhvr/Walker.h"

#define DELTA_THRESH 0.002f

namespace bhvr {

bool Walker::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::attr::Transform>() &&
           entity.hasAttribute<attr::Person>() &&
           entity.hasAttribute<attr::Poses>() &&
           entity.hasAttribute<attr::Sprite>();
}

void Walker::updateEntity(const da::EntityPtr &entity) {
    // Only update once per millisecond
    mTime += getDelta();
    if (mTime < sf::milliseconds(1)) {
        return;
    }
    mTime = sf::Time::Zero;
    
    // Get attributes
    da::attr::Transform &xform = entity->getAttribute<da::attr::Transform>();
    attr::Poses &poses = entity->getAttribute<attr::Poses>();
    attr::Sprite &sprite = entity->getAttribute<attr::Sprite>();
    sf::Vector2f &prevPos =
        entity->getAttribute<attr::Person>().previousPosition;
    
    // Make sure they're enabled.  Early out if they're not.
    if (!poses.isEnabled || !sprite.isEnabled()) {
        return;
    }
    
    // Get change in position
    sf::Vector2f deltaPos = xform.getPosition() - prevPos;
    prevPos = xform.getPosition();
    
    float distance = da::MathHelper::length(deltaPos.x, deltaPos.y);
    
    // Don't bother if the distance is too small.  We may regret this on the
    // magical computers of tomorrow (or if we forget to limit the framerate)
    if (distance < DELTA_THRESH) {
        return;
    }
    
    // Calculate the angle of movement.
    float angle = atan2(deltaPos.y, deltaPos.x);
    
    // atan2 yields [-pi, +pi], so let's correct it to something more palatable:
    // [0, 2pi]
    if (angle < 0.f) {
        angle += da::MathHelper::TwoPi;
    }
    
    // Threshold checking
    float center = 0.f;
    for (unsigned int i = 0; i < DirectionCount; i++) {        
        if (angle > center - da::MathHelper::PiOverEight &&
            angle <= center + da::MathHelper::PiOverEight) {
            poses.direction = (CardinalDirection)i;
            break;
        }
        
        center += da::MathHelper::PiOverFour;
    }
}

}
