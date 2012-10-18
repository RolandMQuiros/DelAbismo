#ifndef DA_ANIMATION_H
#define DA_ANIMATION_H

#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "da/ContentTypes.h"

namespace da {

class Animation : public sf::Drawable {
public:    
    struct Frame {
        sf::IntRect subrect;
        sf::Time duration;
    };
    
    enum Status {
        Playing,
        Paused,
        Stopped
    };
    
    Animation(const TexturePtr &texture=TexturePtr());
    Animation(const Animation &other);
    Animation &operator=(const Animation &other);
    
    void setTexture(const TexturePtr &texture);
    TexturePtr getTexture() const;
    
    void addFrame(const sf::IntRect &subrect,
                  const sf::Time &duration=sf::Time::Zero);
    void addFrame(const Frame &frame);
    
    void setCurrentFrame(unsigned int frame);
    const Frame &getCurrentFrame() const;
    unsigned int getCurrentFrameIndex() const;
    
    unsigned int getFrameCount() const;
    
    void setSpeed(float speed);
    float getSpeed() const;
    
    void setReverse(bool reverse);
    bool isReverse() const;
    
    void setRepeat(int Repeat);
    int getRepeat() const;
    unsigned int getCurrentRepeat() const;
    
    void play();
    void play(unsigned int frame);
    void pause();
    void pause(unsigned int frame);
    void stop(unsigned int frame=0); 
    Status getStatus() const;
    
    void update(const sf::Time &deltaTime);
    
private:
    std::vector<Frame> mFrames;
    sf::Sprite mDisplay;
    TexturePtr mTexture;
    
    Status mStatus;
    sf::Time mTime;
    float mSpeed;
    bool mIsReverse;
    unsigned int mCurrentFrame;
    int mRepeat;
    unsigned int mRepeatCount;
    
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    
};
    
}

#endif
