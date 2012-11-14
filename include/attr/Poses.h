#ifndef ATTR_POSES_H
#define ATTR_POSES_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <da/Attribute.h>

namespace bhvr {
    class Poses;
}

namespace attr {

/**
 * Holds a dictionary of frames, each a subrectangle of the sprite texture.
 * Consequently, relies on attr::Sprite to display properly.
 * Each frame is displayed for a certain amount of time, defined by
 * Poses::timePerFrame.
 */
class Poses : public da::Attribute<Poses> {
public:
    /** Whether or not to use this Attribute for rendering */
    bool isEnabled;
    /** Whether we can manually change the current pose. Used for scene
        scripts */
    bool isLocked;
    
    bool isLoop;
    bool isReverse;
    
    sf::Time time;
    sf::Time timePerFrame;
    
    Poses();
    
    unsigned int getPoseCount() const;
    bool hasPose(const std::string &name) const;
    void addFrame(const std::string &name, const sf::IntRect &frame);
    unsigned int getFrameCount(const std::string &poseName) const;
    
    bool nextFrame();
    void setCurrentFrame(const std::string &poseName, unsigned int index=0);
    sf::IntRect getCurrentFrame() const;
    unsigned int getCurrentFrameIndex() const;
private:
    typedef std::unordered_map<const char *, std::vector<sf::IntRect> > PoseMap;
    PoseMap mPoses;
    
    PoseMap::iterator mCurrentPose;
    unsigned int mCurrentFrame;
};

}

#endif
