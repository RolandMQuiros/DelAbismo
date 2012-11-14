#include "attr/Poses.h"

namespace attr {

Poses::Poses() :
isEnabled(true),
isLocked(false),
isLoop(true),
isReverse(false),
direction(South),
mCurrentPose(mPoses.end()),
mFrameIndex(0) {
    
}

void Poses::addPose(const std::string &name, const Pose &pose) {
    mPoses[name.c_str()] = pose;
}

void Poses::setPose(const std::string &name, unsigned int index) {
    std::unordered_map<const char *, Pose>::const_iterator iter =
        mPoses.find(name.c_str());
    
    if (iter == mPoses.end()) {
        return;
    }
    
    if (iter->second.getFrameCount() > index) {
        mCurrentPose = iter;
        mFrameIndex = index;
    }
}

void Poses::setFrame(unsigned int index) {
    if (mCurrentPose->second.getFrameCount() > index) {
        mFrameIndex = index;
    }
}

Pose::Frame Poses::getFrame() const {
    Pose::Frame ret;
    
    if (mCurrentPose != mPoses.end()) {
        ret = mCurrentPose->second.getFrame(direction, mFrameIndex);
    }
    
    return ret;
}

bool Poses::nextFrame() {
    if (mCurrentPose != mPoses.end()) {
        unsigned int numFrames = mCurrentPose->second.getFrameCount();
        
        if (mFrameIndex < numFrames) {
            // Decrement if reversed
            mFrameIndex += (isReverse) ? -1 : 1;
            
            if (isLoop) {
                mFrameIndex %= numFrames;
            }
            
            return true;
        }
    }
    
    return false;
}

}
