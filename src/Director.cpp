#include "attr/Actor.h"
#include "scene/Scene.h"
#include "Director.h"

Director *Director::msInstance = NULL;

Director::~Director() {
    lua_close(mLua);
}

Director &Director::getInstance() {
    if (msInstance == NULL) {
        msInstance = new Director();
    }
    
    return *msInstance;
}

void Director::addEntity(const std::string &name, const da::EntityRef &entity) {
    mEntities[name] = entity;
}

void Director::addEntity(const std::string &name, const da::EntityPtr &entity) {
    if (entity) {
        mEntities[name] = da::EntityRef(entity);
    }
}

void Director::addActor(const da::EntityRef &entity) {
    da::EntityPtr ptr = entity.lock();
    if (!ptr || !ptr->hasAttribute<attr::Actor>()) {
        return;
    }
    
    std::string name = ptr->getAttribute<attr::Actor>().name;
    if (name.empty()) {
        return;
    }
    
    mEntities[name] = entity;
}

void Director::addActor(const da::EntityPtr &entity) {
    if (!entity || !entity->hasAttribute<attr::Actor>()) {
        return;
    }
    
    std::string name = entity->getAttribute<attr::Actor>().name;
    if (name.empty()) {
        return;
    }
    
    mEntities[name] = da::EntityRef(entity);
}

da::EntityRef Director::getEntity(const std::string &name) const {
    std::map<std::string, da::EntityRef>::const_iterator search =
        mEntities.find(name);
    da::EntityRef ret;
    
    if (search != mEntities.end()) {
        ret = search->second;
    }
    
    return ret;
}

void Director::setProgression(Progression progress) {
    mProgression = progress;
}

Director::Progression Director::getProgression() const {
    return mProgression;
}

void Director::addTarget(const std::string &name) {
    std::map<std::string, da::EntityRef>::iterator search =
        mEntities.find(name);
    
    if (search == mEntities.end()) {
        return;
    }
    
    EntityCommandMap::iterator target = mActiveTargets.find(search->second);
    
    if (target == mActiveTargets.end()) {
        mActiveTargets[search->second] = 1;
    } else {
        target->second++;
    }
}

void Director::registerCallback(const std::string &name,
                                int callback(lua_State *)) {
    // Get scene namespace table
    lua_getglobal(mLua, "scene");
    
    // Push function
    lua_pushcfunction(mLua, callback);
    // Create entry in scene table for the pushed function
    lua_setfield(mLua, -2, name.c_str());
                                    
    // Pop the scene namespace from stack
    lua_pop(mLua, 1);
}

void Director::enqueue(const std::string &filename) {
    lua_State *newThread = lua_newthread(mLua);
    if (newThread == NULL) {
        throw Exception(__EXCEPTSRC__, "Error allocating new Lua thread");
    }
    
    if (luaL_loadfile(newThread, filename.c_str()) &&
        lua_isstring(mLua, -1)) {
        std::string err(lua_tostring(mLua, -1));
        lua_pop(mLua, 1);
        
        throw Exception(__EXCEPTSRC__, "Error loading \"" + filename + "\"" + 
                        err);
    }
    
    mLuaThreads.push(newThread);
}

bool Director::next() {
    if (mLuaThreads.empty()) {
        return false;
    }
    
    int res = lua_resume(mLuaThreads.front(), NULL, 0);
    
    switch (res) {
        case 0: // Finish with no errors
            mLuaThreads.pop();
            break;
        case LUA_ERRRUN: // Runtime, memory, or error handling error
        case LUA_ERRMEM:
        case LUA_ERRERR:
            if (lua_isstring(mLuaThreads.front(), -1)) {
                std::string err(lua_tostring(mLuaThreads.front(), -1));
                lua_pop(mLuaThreads.front(), 1);
                
                throw Exception(__EXCEPTSRC__, "Lua runtime error: " + err);
            }
            mLuaThreads.pop();
            break;
    }
    
    if (mLuaThreads.empty()) {
        return false;
    }
    
    return true;
}

void Director::onFinish(const da::EntityRef &entity) {
    EntityCommandMap::iterator search = mActiveTargets.find(entity);
    
    if (search != mActiveTargets.end()) {
        search->second--;
        
        // Current command finishes
        if (search->second <= 0) {
            mActiveTargets.erase(search);
            
            // If specified, progress once any command in the block is finished
            if (mProgression == Any) {
                mActiveTargets.clear();
            }
        }
    }
    
    if (mActiveTargets.empty()) {
        next();
    }
}

void Director::onFinish(const da::EntityPtr &entity) {
    onFinish(da::EntityRef(entity));
}

void Director::onFinish(const da::Entity &entity) {
    EntityCommandMap::iterator iter;
    
    for (iter = mActiveTargets.begin(); iter != mActiveTargets.end(); iter++) {
        da::EntityPtr ptr = iter->first.lock();
        if (ptr && ptr.get() == &entity) {
            iter->second--;
            
            // Current command finishes
            if (iter->second <= 0) {
                mActiveTargets.erase(iter);
                
                // If specified, progress once any command in the block is
                // finished
                if (mProgression == Any) {
                    mActiveTargets.clear();
                }
            }
            
            break;
        }
    }
}

void Director::onFinish(const std::string &name) {
    std::map<std::string, da::EntityRef>::iterator iter =
        mEntities.find(name);
    
    if (iter != mEntities.end()) {
        onFinish(iter->second);
    }
}

Director::Exception::Exception(const std::string &where, unsigned long line,
                               const std::string &source,
                               const std::string &what) :
DAException(where, line, source, what) { }

Director::Director() :
mProgression(All) {
    // Create a new Lua VM
    mLua = luaL_newstate();
    if (mLua == NULL) {
        throw Exception(__EXCEPTSRC__, "Error allocating Lua State");
    }
    
    luaL_openlibs(mLua);
    
    // Create the scene table and assigns it to the Lua environment
    lua_newtable(mLua);
    lua_setglobal(mLua, "scene");
    
    /* Push common constants/functions */
    // All
    lua_getglobal(mLua, "scene");
    lua_pushnumber(mLua, 1);
    lua_setfield(mLua, -2, "All");
    
    // Any
    lua_pushnumber(mLua, 2);
    lua_setfield(mLua, -2, "Any");
    
    // startBlock()
    lua_pushcfunction(mLua, scene::startBlock);
    lua_setfield(mLua, -2, "startBlock");
    
    // endBlock()
    lua_pushcfunction(mLua, scene::endBlock);
    lua_setfield(mLua, -2, "endBlock");
    
    // Pop scene namespace
    lua_pop(mLua, 1);
}
