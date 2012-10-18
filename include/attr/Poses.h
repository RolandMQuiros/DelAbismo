#ifndef ATTR_POSES_H
#define ATTR_POSES_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

#include <da/Attribute.h>

namespace bhvr {
    class Poses;
}

namespace attr {

class Poses : public da::Attribute<Poses> {
public:
    Poses();
    
    void setEnabled(bool enabled);
    bool isEnabled() const;
    
    unsigned int getPoseCount() const;
    bool hasPose(const std::string &name) const;
    void addFrame(const std::string &name, const sf::IntRect &frame);
    unsigned int getFrameCount(const std::string &poseName) const;
    
    void setLooping(bool loop);
    bool isLooping() const;
    
    void setReverse(bool reverse);
    bool isReverse() const;
    
    bool nextFrame();
    void setCurrentPose(const std::string &poseName, unsigned int frame=0);
    void setCurrentFrame(unsigned int frame);
    unsigned int getCurrentFrame() const;
    
    /**
     * Sets amount of time per frame
     */
    void setTimePerFrame(const sf::Time &time);
    const sf::Time &getTimePerFrame() const;
    
    void update(const sf::Time &deltaTime);
private:
    friend class bhvr::Poses;
    typedef std::unordered_map<const char *, std::vector<sf::IntRect> >
        PoseMap;

    bool mIsEnabled;
    PoseMap mPoses;
    
    bool mIsLoop;
    bool mIsReverse;
    
    sf::Time mTime;
    sf::Time mTimePerFrame;
    
    PoseMap::iterator mCurrentPose;
    unsigned int mCurrentFrame;
    
};

}

#endif
