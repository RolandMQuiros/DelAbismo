#include "scene/Scene.h"

namespace scene {

int startBlock(lua_State *L) {
    Director::Progression progression = Director::All;
    
    // Get number of arguments.  No arguments provided defaults to All
    // progression.
    int n = lua_gettop(L);
    if (n > 1) {
        return 0;
    } else if (n == 1) {
        // Set progression
        int number = lua_tonumber(L, 1);
        switch (number) {
            case 1:
                progression = Director::All;
                break;
            case 2:
                progression = Director::Any;
        }
    }
    
    // Apply progression to Director
    Director &director = Director::getInstance();
    director.setProgression(progression);
    
    return 0;
}

int endBlock(lua_State *L) {
    return lua_yield(L, lua_gettop(L));
}

}
