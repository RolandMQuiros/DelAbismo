#ifndef POSE_H
#define POSE_H

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "CardinalDirection.h"

/**
 * A pose is a collection of animations which correspond to a single action,
 * but viewed from different angles.
 * 
 * Every individual animation must have the same number of frames as the others
 * in the pose, such that you can 'rotate' the object at any point and maintain
 * continuity.
 * 
 * Poses can be seen from eight directions.  I'm putting my foot down, here.
 */
class Pose {
public:
    struct Frame {
        sf::IntRect rect;
        sf::Vector2f origin;
    };
    
    /**
     * Constructs a new pose, with the given number of frames.
     * @param $frames
     *   Number of frames per animation stored in this Pose
     */
    Pose(unsigned int frames=1);
    
    Pose(const Pose &other);
    Pose &operator=(const Pose &other);
    
    /**
     * Sets the frame for the given direction and index
     */
    void setFrame(CardinalDirection direction, unsigned int index,
                  const Frame &frame);
    void setFrames(CardinalDirection direction, Frame *frames);
    
    /**
     * Retrieves the frame for the given direction and index
     */
    const Frame &getFrame(CardinalDirection direction,
                          unsigned int index) const;
    
    unsigned int getFrameCount() const;
    
private:
    std::vector<Frame> mFrames[DirectionCount];
    unsigned int mFrameCount;
    
};
 
#endif