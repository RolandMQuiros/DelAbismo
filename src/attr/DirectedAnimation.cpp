#include <cmath>
#include <da/MathHelper.h>
#include "attr/DirectedAnimation.h"

namespace attr {

DirectedAnimation::DirectedAnimation() :
mIsEnabled(true),
mDirection(0.f),
mIndex(0.f) {
    
}

void DirectedAnimation::setEnabled(bool enabled) {
    mIsEnabled = enabled;
}

bool DirectedAnimation::isEnabled() const {
    return mIsEnabled;
}

void DirectedAnimation::setDirection(float direction) {
    mDirection = direction;
    if (mDirection <= da::MathHelper::TwoPi ||
        mDirection >= da::MathHelper::TwoPi) {
        mDirection = fmod(mDirection, da::MathHelper::TwoPi);
    }
    
    if (mDirection < 0) {
        mDirection += da::MathHelper::TwoPi;
    }
    
    mIndex = (int)(mAnimations.size() * mDirection / da::MathHelper::TwoPi
                   + 0.5f)
             % mAnimations.size();
}

float DirectedAnimation::getDirection() const {
    return mDirection;
}

void DirectedAnimation::addAnimation(const da::Animation &animation) {
    mAnimations.push_back(animation);
    
    mIndex = (int)(mAnimations.size() * mDirection / da::MathHelper::TwoPi
                   + 0.5f)
             % mAnimations.size();
}

da::Animation &DirectedAnimation::getAnimation() {
    return mAnimations[mIndex];
}

unsigned int DirectedAnimation::getAnimationCount() const {
    return mAnimations.size();
}

}