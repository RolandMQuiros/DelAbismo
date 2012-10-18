#ifndef ATTR_DIRECTEDANIMATION_H
#define ATTR_DIRECTEDANIMATION_H

#include <da/Attribute.h>
#include <da/twod/Animation.h>

namespace attr {

/**
 * Represents an animation that depicts the same thing, from different angles
 */    
struct DirectedAnimation : public da::Attribute<DirectedAnimation> {
public:
    DirectedAnimation();
    
    void setEnabled(bool enabled);
    bool isEnabled() const;
    
    void setDirection(float direction);
    float getDirection() const;
    
    void addAnimation(const da::Animation &animation);
    da::Animation &getAnimation();
    unsigned int getAnimationCount() const;
private:
    /** Whether or not this Attribute is drawn */
    bool mIsEnabled;
    /** Animations.  Each one added represents a different direction */
    std::vector<da::Animation> mAnimations;
    /** Index of the used animation */
    unsigned int mIndex;
    /** Direction of this animation, in radians */
    float mDirection;
};

}

#endif
