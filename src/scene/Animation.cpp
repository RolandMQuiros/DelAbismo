#include "scene/Animation.h"

#include "attr/Poses.h"

namespace scene {


int playPose(lua_State *L) {
    int n = lua_gettop(L);
    
    // Make sure we have the right number and types of arguments
    if (n != 4 ||
        !lua_isstring(L, 1) && !lua_isstring(L, 2) &&
        !lua_isnumber(L, 3) && !lua_isboolean(L, 4)) {
        return 0;
    }
    
    // Get director instance
    Director &director = Director::getInstance();
    
    // Get arguments
    std::string targetName = lua_tostring(L, 1);
    std::string poseName = lua_tostring(L, 2);
    float speed = lua_tonumber(L, 3);
    bool loop = lua_toboolean(L, 4);
    
    // Find target entity
    da::EntityPtr target = director.getEntity(targetName).lock();
    if (!target) {
        return 0;
    }
    
    // Set the current pose
    attr::Poses &poses = target->getAttribute<attr::Poses>();
    
    // Make sure we have the appropriate pose
    if (!poses.hasPose(poseName)) {
        return 0;
    }
    
    // Set the pose
    poses.setCurrentFrame(poseName);
    
    // Set loop, reverse, and speed
    poses.isLoop = loop;
    if (speed < 0.f) {
        poses.isReverse = true;
    }
    poses.time = sf::Time::Zero;
    poses.timePerFrame = sf::seconds(1.f / speed);
    
    // Enable and lock pose
    poses.isEnabled = true;
    poses.isLocked = true;
    
    return 0;
}

int releasePose(lua_State *L) {
    int n = lua_gettop(L);
    
    if (n != 1 || !lua_isstring(L, 1)) {
        return 0;
    }
    
    // Find target entity
    std::string targetName = lua_tostring(L, 1);
    da::EntityPtr target = director.getEntity(targetName).lock();
    if (!target) {
        return 0;
    }
    
    // Unlock the pose
    attr::Poses &poses = target->getAttribute<attr::Poses>();
    poses.isLocked = false;
}

}