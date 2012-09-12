#include <SFML/Graphics/RenderTarget.hpp>

#include "da/Animation.h"
#include "da/StringHelper.h"
#include "rapidxml/rapidxml.hpp"

namespace da {
    
Animation::Animation() :
mPlay(false),
mReverse(false),
mFrame(0),
mFrameCount(0),
mLoop(0),
mLoopCount(0),
mSpeed(0.f),
mTime(0.f) {
}

Animation::Animation(Animation const &other) :
mTexture(other.mTexture),
mSprite(other.mSprite),
mFrames(other.mFrames),
mPlay(other.mPlay),
mReverse(other.mReverse),
mFrame(other.mFrame),
mFrameCount(other.mFrameCount),
mLoop(other.mLoop),
mSpeed(other.mTime),
mTime(other.mTime) {
}

Animation &Animation::operator=(Animation const &other) {
    mTexture = other.mTexture;
    mSprite = other.mSprite;
    mFrames = other.mFrames;
    mPlay = other.mPlay;
    mReverse = other.mReverse;
    mFrame = other.mFrame;
    mFrameCount = other.mFrameCount;
    mLoop = other.mLoop;
    mSpeed = other.mTime;
    mTime = other.mTime;
    
    return *this;
}

void Animation::setTexture(TexturePtr texture) {
    mTexture = texture;
    mSprite.setTexture(*mTexture);
}

TexturePtr Animation::getTexture() const {
    return mTexture;
}

void Animation::addFrame(sf::IntRect const &rect, sf::RenderStates states,
                         const sf::Color &color) {
    Frame frame;
    frame.rectangle = rect;
    frame.states = states;
    frame.color = color;
    
    // set first frame as the default
    if (mFrames.empty()) {
        mSprite.setTextureRect(rect);
        mSprite.setColor(color);
    }
    
    mFrames.push_back(frame);
}

void Animation::setFrame(unsigned int frame) {
    if (frame < mFrames.size()) {
        mFrame = frame;
    }
}

unsigned int Animation::getFrame() const {
    return mFrame;
}

void Animation::setFramesPerSecond(float fps) {
    if (fps > 0.f) {
        mSpeed = 1.f / fps;
    }
}

float Animation::getFramesPerSecond() const {
    return 1.f / mSpeed;
}

void Animation::setSecondsPerFrame(float spf) {
    mSpeed = spf;
}

float Animation::getSecondsPerFrame() const {
    return mSpeed;
}

void Animation::setTime(float time) {
    if (!mFrames.empty()) {
        mSpeed = time / mFrames.size();
    }
}

float Animation::getTime() const {
    return mSpeed * mFrames.size();
}

void Animation::setLoop(int loop) {
    mLoop = loop;
}

int Animation::getLoop() const {
    return mLoop;
}

void Animation::setReverse(bool reverse) {
    mReverse = reverse;
}

bool Animation::isReverse() const {
    return mReverse;
}

void Animation::play() {
    if (!mFrames.empty()) {
        mPlay = true;
        mTime = 0.f;

        mFrameCount = 0;
        mLoopCount = mLoop;
    }
}

void Animation::play(unsigned int frame) {
    if (!mFrames.empty()) {
        mPlay = true;
        mTime = 0.f;

        mFrame = frame;
        mFrameCount = 0;
        mLoopCount = mLoop;
    }
}

void Animation::stop() {
    mPlay = false;
    mTime = 0.f;
}

void Animation::stop(unsigned int frame) {
    mPlay = false;
    mTime = 0.f;
    if (frame < mFrames.size()) {
        mFrame = frame;
    }
}

bool Animation::isPlaying() const {
    return mPlay;
}

bool Animation::isEmpty() const {
    return mFrames.empty() || !mTexture;
}

void Animation::update(const sf::Time &deltaTime) {
    if (mPlay) {
        mTime += deltaTime.asSeconds();
        if (mTime > mSpeed) {
            mTime = 0.f;
            mFrame = (mFrame + (mReverse ? -1 : 1)) % mFrames.size();
            mFrameCount++;
            
            mSprite.setTextureRect(mFrames[mFrame].rectangle);
            mSprite.setColor(mFrames[mFrame].color);

            if (mFrameCount >= mFrames.size() && mLoopCount != 0) {
                mFrameCount = 0;
                
                if (mLoopCount > 0) {
                    mLoopCount--;
                }
                
                if (mLoopCount == 0) {
                    mPlay = false;
                }
            }
        }
    }
}

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!mFrames.empty()) {
        target.draw(mSprite, states);
    }
}
    
}
