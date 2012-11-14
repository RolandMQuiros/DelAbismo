#ifndef ATTR_POSES_H
#define ATTR_POSES_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/System/Time.hpp>
#include <da/Attribute.h>

#include "Pose.h"

namespace attr {

/**
 * Holds a dictionary of frames, each a subrectangle of the sprite texture.
 * Consequently, relies on attr::Sprite to display properly.
 * Each frame is displayed for a certain amount of time, defined by
 * Poses::timePerFrame.
 */
class Poses : public da::Attribute<Poses> {
public:
    bool isEnabled;
    bool isLocked;
    bool isReverse;
    bool isLoop;
    
    CardinalDirection direction;
    
    sf::Time time;
    sf::Time timePerFrame;
    
    Poses();
    
    void addPose(const std::string &name, const Pose &pose);
    void setPose(const std::string &name, unsigned int index=0);
    
    void setFrame(unsigned int index);
    Pose::Frame getFrame() const;
    
    bool nextFrame();
private:
    std::unordered_map<const char *, Pose> mPoses;
    std::unordered_map<const char *, Pose>::const_iterator mCurrentPose;

    unsigned int mFrameIndex;

};

}

#endif
