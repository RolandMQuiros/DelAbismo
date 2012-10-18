#include "attr/Poses.h"

namespace attr {

Poses::Poses() :
mIsEnabled(true),
mIsLoop(true),
mIsReverse(false),
mCurrentPose(mPoses.end()),
mCurrentFrame(0) {
    
}

void Poses::setEnabled(bool enabled) {
    mIsEnabled = enabled;
}

bool Poses::isEnabled() const {
    return mIsEnabled;
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

void Poses::setCurrentPose(const std::string &poseName, unsigned int frame) {
    PoseMap::iterator search = mPoses.find(poseName.c_str());
    if (search != mPoses.end()) {
        mCurrentPose = search;
        mCurrentFrame = frame % search->second.size();
    }
}

void Poses::setLooping(bool loop) {
    mIsLoop = loop;
}

bool Poses::isLooping() const {
    return mIsLoop;
}

void Poses::setReverse(bool reverse) {
    mIsReverse = reverse;
}

bool Poses::isReverse() const {
    return mIsReverse;
}


bool Poses::nextFrame() {
    bool ret = true;
    
    if (mCurrentPose != mPoses.end()) {
        unsigned int poseLength = mCurrentPose->second.size();
        
        if (mIsReverse) {
            mCurrentFrame--;
        } else {
            mCurrentFrame++;
        }
        
        if (mIsLoop || mCurrentFrame < poseLength) {
            mCurrentFrame %= poseLength;
        } else {
            ret = false;
        }
    }
    
    return ret;
}

void Poses::setCurrentFrame(unsigned int frame) {
    if (mCurrentPose != mPoses.end()) {
        mCurrentFrame = frame % mCurrentPose->second.size();
    }
}

unsigned int Poses::getCurrentFrame() const {
    return mCurrentFrame;
}

void Poses::setTimePerFrame(const sf::Time &time) {
    mTimePerFrame = time;
}

const sf::Time &Poses::getTimePerFrame() const {
    return mTimePerFrame;
}

void Poses::update(const sf::Time &deltaTime) {
    mTime += deltaTime;
    if (mTime > mTimePerFrame) {
        nextFrame();
    }
}
    
}
