#include "attr/Poses.h"

namespace attr {

Poses::Poses() :
isEnabled(true),
isLoop(true),
isReverse(false),
mCurrentPose(mPoses.end()),
mCurrentFrame(0) {
    
}

unsigned int Poses::getPoseCount() const {
    return mPoses.size();
}

bool Poses::hasPose(const std::string &poseName) const {
    return mPoses.find(poseName.c_str()) == mPoses.end();
}

void Poses::addFrame(const std::string &name, const sf::IntRect &frame) {
    mPoses[name.c_str()].push_back(frame);
}

unsigned int Poses::getFrameCount(const std::string &poseName) const {
    unsigned int ret = 0;
    
    PoseMap::const_iterator search = mPoses.find(poseName.c_str());
    if (search != mPoses.end()) {
        ret = search->second.size();
    }
    
    return ret;
}

bool Poses::nextFrame() {
    if (mCurrentPose != mPoses.end()) {
        unsigned int numFrames = mCurrentPose->second.size();
        
        if (mCurrentFrame < numFrames) {
            // Decrement if reversed
            mCurrentFrame += (isReverse) ? -1 : 1;
            
            if (isLoop) {
                mCurrentFrame %= numFrames;
            }
            
            return true;
        }
    }
    
    return false;
}

void Poses::setCurrentFrame(const std::string &poseName, unsigned int index) {
    if (isLocked) {
        return;
    }
    
    PoseMap::iterator search = mPoses.find(poseName.c_str());
    if (search != mPoses.end() && index < search->second.size()) {
        mCurrentPose = search;
        mCurrentFrame = index;
    }
}

sf::IntRect Poses::getCurrentFrame() const {
    if (mCurrentPose != mPoses.end() &&
        mCurrentFrame < mCurrentPose->second.size()) {
        return mCurrentPose->second[mCurrentFrame];
    }
    
    return sf::IntRect();
}
    
}
