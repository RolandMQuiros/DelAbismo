#include <SFML/Graphics/RenderTarget.hpp>

#include "da/Animation.h"
#include "da/Helper.h"
#include "rapidxml/rapidxml.hpp"

namespace da {
    
Animation::Animation() :
mvPlay(false),
mvReverse(false),
mvFrame(0),
mvFrameCount(0),
mvLoop(0),
mvLoopCount(0),
mvSpeed(0.f),
mvTime(0.f) {
}

Animation::Animation(Animation const &other) :
mvTexture(other.mvTexture),
mvSprite(other.mvSprite),
mvFrames(other.mvFrames),
mvPlay(other.mvPlay),
mvReverse(other.mvReverse),
mvFrame(other.mvFrame),
mvFrameCount(other.mvFrameCount),
mvLoop(other.mvLoop),
mvSpeed(other.mvTime),
mvTime(other.mvTime) {
}

Animation &Animation::operator=(Animation const &other) {
    mvTexture = other.mvTexture;
    mvSprite = other.mvSprite;
    mvFrames = other.mvFrames;
    mvPlay = other.mvPlay;
    mvReverse = other.mvReverse;
    mvFrame = other.mvFrame;
    mvFrameCount = other.mvFrameCount;
    mvLoop = other.mvLoop;
    mvSpeed = other.mvTime;
    mvTime = other.mvTime;
    
    return *this;
}

void Animation::setTexture(TexturePtr texture) {
    mvTexture = texture;
    mvSprite.setTexture(*mvTexture);
}

TexturePtr Animation::getTexture() const {
    return mvTexture;
}

void Animation::addFrame(sf::IntRect const &rect, sf::RenderStates states,
                         const sf::Color &color) {
    Frame frame;
    frame.rectangle = rect;
    frame.states = states;
    frame.color = color;
    
    // set first frame as the default
    if (mvFrames.empty()) {
        mvSprite.setTextureRect(rect);
        mvSprite.setColor(color);
    }
    
    mvFrames.push_back(frame);
}

void Animation::setFrame(unsigned int frame) {
    if (frame < mvFrames.size()) {
        mvFrame = frame;
    }
}

unsigned int Animation::getFrame() const {
    return mvFrame;
}

void Animation::setFramesPerSecond(float fps) {
    if (fps > 0.f) {
        mvSpeed = 1.f / fps;
    }
}

float Animation::getFramesPerSecond() const {
    return 1.f / mvSpeed;
}

void Animation::setSecondsPerFrame(float spf) {
    mvSpeed = spf;
}

float Animation::getSecondsPerFrame() const {
    return mvSpeed;
}

void Animation::setTime(float time) {
    if (!mvFrames.empty()) {
        mvSpeed = time / mvFrames.size();
    }
}

float Animation::getTime() const {
    return mvSpeed * mvFrames.size();
}

void Animation::setLoop(int loop) {
    mvLoop = loop;
}

int Animation::getLoop() const {
    return mvLoop;
}

void Animation::setReverse(bool reverse) {
    mvReverse = reverse;
}

bool Animation::isReverse() const {
    return mvReverse;
}

void Animation::play() {
    if (!mvFrames.empty()) {
        mvPlay = true;
        mvTime = 0.f;

        mvFrameCount = 0;
        mvLoopCount = mvLoop;
    }
}

void Animation::play(unsigned int frame) {
    if (!mvFrames.empty()) {
        mvPlay = true;
        mvTime = 0.f;

        mvFrame = frame;
        mvFrameCount = 0;
        mvLoopCount = mvLoop;
    }
}

void Animation::stop() {
    mvPlay = false;
    mvTime = 0.f;
}

void Animation::stop(unsigned int frame) {
    mvPlay = false;
    mvTime = 0.f;
    if (frame < mvFrames.size()) {
        mvFrame = frame;
    }
}

bool Animation::isPlaying() const {
    return mvPlay;
}

bool Animation::isEmpty() const {
    return mvFrames.empty() || !mvTexture;
}

void Animation::update(const sf::Time &deltaTime) {
    if (mvPlay) {
        mvTime += deltaTime.asSeconds();
        if (mvTime > mvSpeed) {
            mvTime = 0.f;
            mvFrame = (mvFrame + (mvReverse ? -1 : 1)) % mvFrames.size();
            mvFrameCount++;
            
            mvSprite.setTextureRect(mvFrames[mvFrame].rectangle);
            mvSprite.setColor(mvFrames[mvFrame].color);

            if (mvFrameCount >= mvFrames.size() && mvLoopCount != 0) {
                mvFrameCount = 0;
                
                if (mvLoopCount > 0) {
                    mvLoopCount--;
                }
                
                if (mvLoopCount == 0) {
                    mvPlay = false;
                }
            }
        }
    }
}

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform() * mvFrames[mvFrame].states.transform;
    
    if (!mvFrames.empty()) {
        target.draw(mvSprite, states);
    }
}
    
}
