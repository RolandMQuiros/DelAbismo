#ifndef DA_ANIMATION_H
#define DA_ANIMATION_H

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <SFML/System/Time.hpp>

#include "da/ContentTypes.h"

namespace da {

/**
 *
 */
class Animation : public sf::Drawable, public sf::Transformable {
public:
    /** Constructs an empty animation
     */
    Animation();

    /** Copies an animation
     *  @param other animation to copy
     */
    Animation(const Animation &other);

    Animation &operator=(const Animation &other);

    /** Sets this Animation's texture
     * @param texture texture
     */
    void setTexture(TexturePtr texture);

    /** Adds a frame to the animation.
     * A frame is a sub-rectangle of the texture.
     * @param frame frame rectangle
     * @param states render states
     * @param color render color
     */
    void addFrame(const sf::IntRect &frame,
                  sf::RenderStates states=sf::RenderStates(),
                  const sf::Color &color=sf::Color::White);

    /** Sets the current frame
     * @param frame frame
     */
    void setFrame(unsigned int frame);

    /** Returns the current frame
     * @return frame
     */
    unsigned int getFrame() const;

    /** Set animation timing in frames per second
     * @param fps frames per second.
     */
    void setFramesPerSecond(float fps);

    /** Returns animation timing in frames per second
     * @return frames per second.
     */
    float getFramesPerSecond() const;

    /** Set animating timing in seconds per frame
     * @param spf seconds per frame.
     */
    void setSecondsPerFrame(float spf);

    /** Returns animation timing in seconds per frame
     * @return seconds per frame
     */
    float getSecondsPerFrame() const;

    /** Sets animation timing in seconds
     * Sets the amount of time to play entire animation once.
     * @param time animation time in seconds.
     */
    void setTime(float time);

    /** Returns animation timing in seconds
     * Returns the amount of time to play entire animation once.
     * @return animation time in seconds
     */
    float getTime() const;

    /** Sets number of times to loop.
     * Sets the number of times this animation loops with every call to
     * Play().
     * @param loop number of times to loop.  Negative for indefinite
     * looping.
     */
    void setLoop(int loop);

    /** Returns the number of times to loop.
     * @return number of times to loop
     */
    int getLoop() const;

    /** Set whether or not the animation plays in reverse
     * @param reverse true to play in reverse
     */
    void setReverse(bool reverse);

    /** Returns true if animation is set to play in reverse
     * @return true if reversed.  false, otherwise
     */
    bool isReverse() const;

    /** Plays the animation.
     */
    void play();

    /** Plays the animation, starting at the given frame.
     * @param frame first frame of the animation played
     */
    void play(unsigned int frame);

    /** Stops the animation at its current frame.
     */
    void stop();

    /** Stops the animation at a specified frame.
     * @param frame frame to stop animation at
     */
    void stop(unsigned int frame);

    /** Returns true if animation is currently playing
     * @return true if playing.  False, otherwise
     */
    bool isPlaying() const;

    /** Returns true if animation contains no frames or texture.
     * @param true if no frames or texture has been set.  False, otherwise.
     */
    bool isEmpty() const;

    /** Updates this animation
     * @param deltaTime time between updates, in seconds
     */
    void update(const sf::Time &deltaTime);

private:
    struct Frame {
        sf::IntRect rectangle;
        sf::RenderStates states;
        sf::Color color;
    };
    
    TexturePtr mvTexture;
    sf::Sprite mvSprite;
    std::vector<Frame> mvFrames;

    bool mvPlay;
    bool mvReverse;

    unsigned int mvFrame;
    unsigned int mvFrameCount;

    int mvLoop;
    int mvLoopCount;

    float mvSpeed;
    float mvTime;
    
    /** Renders this animation
     * @param target reference to display
     * @param states render states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

}

#endif
