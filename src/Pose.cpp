#include "Pose.h"

Pose::Pose(unsigned int frames) :
mFrameCount(frames) {
    // Resize each vector
    for (unsigned int i = 0; i < DirectionCount; i++) {
        mFrames[i].resize(mFrameCount);
    }
}

void Pose::setFrame(CardinalDirection direction, unsigned int index,
                    const Frame &frame) {
    // Only apply if we're in bounds
    if (index < mFrameCount) {
        mFrames[direction][index] = frame;
    }
}

const Pose::Frame &Pose::getFrame(CardinalDirection direction,
                                  unsigned int index) const {
    if (index < mFrameCount) {
        return mFrames[direction][index];
    }
}