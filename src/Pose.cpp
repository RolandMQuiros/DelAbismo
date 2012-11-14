#include "Pose.h"

Pose::Pose(unsigned int frames) :
mFrameCount(frames > 0 ? frames : 1) {
    // Resize each vector
    for (unsigned int i = 0; i < DirectionCount; i++) {
        mFrames[i].resize(mFrameCount);
    }
}

Pose::Pose(const Pose &other) :
mFrameCount(other.mFrameCount) {
    for (unsigned int i = 0; i < DirectionCount; i++) {
        mFrames[i] = other.mFrames[i];
    }
}

Pose &Pose::operator=(const Pose &other) {
    for (unsigned int i = 0; i < DirectionCount; i++) {
        mFrames[i] = other.mFrames[i];
    }
    
    mFrameCount = other.mFrameCount;
    
    return *this;
}

void Pose::setFrame(CardinalDirection direction, unsigned int index,
                    const Frame &frame) {
    // Only apply if we're in bounds
    if (index < mFrameCount) {
        mFrames[direction][index] = frame;
    }
}

void Pose::setFrames(CardinalDirection direction, Frame *frames) {
    for (unsigned int i = 0; i < mFrameCount; i++) {
        mFrames[direction][i] = frames[i];
    }
}

const Pose::Frame &Pose::getFrame(CardinalDirection direction,
                                  unsigned int index) const {
    if (index < mFrameCount) {
        return mFrames[direction][index];
    }
}

unsigned int Pose::getFrameCount() const {
    return mFrameCount;
}
