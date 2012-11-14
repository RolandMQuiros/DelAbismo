/**
 * This file includes the basic, and most common scene command functions.
 */
#ifndef SCENE_H
#define SCENE_H

#include "Director.h"

namespace scene {

/**
 * Indicates the beginning of a scene block
 * @param $L
 *   Lua virtual machine state
 * @return 
 *   Number of return values pushed onto the stack
 */
int startBlock(lua_State *L);

int endBlock(lua_State *L);
    
}

#endif
