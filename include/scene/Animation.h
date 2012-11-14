/**
 * Scene functions having to do with setting animation-related Attributes, 
 * manipulating attr::Sprite, or attr::Poses, and ilk.
 */

#ifndef SCENE_ANIMATION_H
#define SCENE_ANIMATION_H

#include "Director.h"

namespace scene {

/**
 * Sets an entity's current Pose, and animates it.  Overrides directional
 * poses until released.  Will loop animation if told to, but stops at the last
 * frame in the pose otherwise.
 * 
 * In Lua:
 * @code
 *     scene.setPose("poseName", "pose", speed, loopCount)
 * @endcode
 * 
 * A negative speed indicates playing the animation in reverse
 */
int setPose(lua_State *L);

/**
 * Releases an entity from a pose animation
 */
int releasePose(lua_State *L);

}

#endif
