#ifndef ATTR_MOTIONQUEUE_H
#define ATTR_MOTIONQUEUE_H

#include <queue>
#include <SFML/System/Vector2.hpp>
#include <da/Attribute.h>
#include "CardinalDirection.h"

namespace attr {

struct MotionQueue : public da::Attribute<MotionQueue> {
    struct Motion {
        float direction;
        float distance;
        float speed;
    };
    
    /** List of motions */
    std::queue<Motion> motions;
    /** Current motion vector */
    sf::Vector2f displacement;
};

}

#endif
