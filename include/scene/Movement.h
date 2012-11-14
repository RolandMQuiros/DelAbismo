#ifndef SCENE_MOVEMENT_H
#define SCENE_MOVEMENT_H

#include "Director.h"

namespace scene {

/**
 * Enqueues a motion onto a entity.  Relies on attr::MotionQueue.
 */
int move(lua_State *L);

}

#endif
