#ifndef ATTR_DIRECTEDANIMATION_H
#define ATTR_DIRECTEDANIMATION_H

#include <da/Attribute.h>
#include <da/Animation.h>

namespace attr {

/**
 * Represents an animation that depicts the same thing, from different angles
 */    
struct DirectedAnimation : public da::Attribute<DirectedAnimation> {
    /** Animations.  Each one added represents a different direction */
    std::vector<da::Animation> animations;
    unsigned int index;
};

}

#endif
