#include <SFML/Graphics/RenderTarget.hpp>
#include <rapidxml/rapidxml.hpp>
#include "da/twod/Animation.h"

namespace da {

Animation::Animation(const TexturePtr &texture) :
mStatus(Stopped),
mTexture(texture),
mSpeed(1.f),
mIsReverse(false),
mCurrentFrame(0),
mRepeat(-1),
mRepeatCount(0) {
}

Animation::Animation(const Animation &other) :
mFrames(other.mFrames),
mTexture(other.mTexture),
mDisplay(other.mDisplay),
mStatus(other.mStatus),
mTime(other.mTime),
mSpeed(other.mSpeed),
mIsReverse(other.mIsReverse),
mCurrentFrame(other.mCurrentFrame),
mRepeat(other.mRepeat),
mRepeatCount(other.mRepeatCount)  {
}

Animation &Animation::operator=(const Animation &other) {
    mFrames = other.mFrames;
    mTexture = other.mTexture;
    mDisplay = other.mDisplay;
    mStatus = other.mStatus;
    mSpeed = other.mSpeed;
    mIsReverse = other.mIsReverse;
    mCurrentFrame = other.mCurrentFrame;
    mRepeat = other.mRepeat;
    mRepeatCount = other.mRepeatCount;
    
    return *this;
}

void Animation::setTexture(const TexturePtr &texture) {
    if (texture) {
        mTexture = texture;
        mDisplay.setTexture(*texture);
    }
}

TexturePtr Animation::getTexture() const {
    return mTexture;
}

void Animation::addFrame(const sf::IntRect &subrect,
                         const sf::Time &duration) {
    Frame frame = {
        subrect,
        duration,
    };
    
    // Use the first frame by default
    if (mFrames.empty()) {
        mDisplay.setTextureRect(subrect);
    }
    
    mFrames.push_back(frame);
}

void Animation::setCurrentFrame(unsigned int frame) {
    if (frame < mFrames.size()) {
        mCurrentFrame = frame;
    }
}

const Animation::Frame &Animation::getCurrentFrame() const {
    return mFrames[mCurrentFrame];
}

unsigned int Animation::getCurrentFrameIndex() const {
    return mCurrentFrame;
}

unsigned int Animation::getFrameCount() const {
    return mFrames.size();
}

void Animation::setSpeed(float speed) {
    mSpeed = speed;
    if (mSpeed < 0.f) {
        mSpeed = -mSpeed;
        mIsReverse = true;
    }
}

float Animation::getSpeed() const {
    if (mIsReverse) {
        return -mSpeed;
    }
    return mSpeed;
}

void Animation::setReverse(bool reverse) {
    mIsReverse = reverse;
}

bool Animation::isReverse() const {
    return mIsReverse;
}

void Animation::setRepeat(int Repeat) {
    mRepeat = Repeat;
}

int Animation::getRepeat() const {
    return mRepeat;
}

unsigned int Animation::getCurrentRepeat() const {
    return mRepeatCount;
}

void Animation::play() {
    if (!mFrames.empty()) {
        mStatus = Playing;

        mRepeatCount = 0;
    }
}

void Animation::play(unsigned int frame) {
    if (frame < mFrames.size()) {
        mStatus = Playing;
        
        mCurrentFrame = frame;
    }
}

void Animation::pause() {
    mStatus = Paused;
}

void Animation::pause(unsigned int frame) {
    mStatus = Paused;
    
    if (frame < mFrames.size()) {
        mCurrentFrame = frame;
    }
}

void Animation::stop(unsigned int frame) {
    mStatus = Stopped;
    mTime = sf::Time::Zero;
    mRepeatCount = 0;
    
    if (frame < mFrames.size()) {
        mCurrentFrame = frame;
    }
}

Animation::Status Animation::getStatus() const {
    return mStatus;
}

void Animation::update(const sf::Time &deltaTime) {
    if (mStatus == Playing) {
        mTime += deltaTime;
        if (!mFrames.empty() && mTime >= mFrames[mCurrentFrame].duration) {
            mTime = sf::Time::Zero;
            
            if (mIsReverse) {
                mCurrentFrame--;
                if (mRepeatCount <= mRepeat
                    && mCurrentFrame <= 0) {
                    mRepeatCount++;
                }
            } else {
                mCurrentFrame++;
                if (mRepeatCount <= mRepeat
                    && mCurrentFrame >= mFrames.size()) {
                    mRepeatCount++;
                }
            }
            
            if (mRepeat > 0 && mRepeatCount > mRepeat) {
                mStatus = Paused;
                mCurrentFrame--;
            }
            
            mCurrentFrame %= mFrames.size();
            Frame &frame = mFrames[mCurrentFrame];
            
            mDisplay.setTextureRect(frame.subrect);
        }
    }
}

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mDisplay, states);
}

}
