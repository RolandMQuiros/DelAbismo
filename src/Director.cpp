#include "Director.h"

Director::Director() :
mProgression(All) {
    mLua = luaL_newstate();
    if (mLua == NULL) {
        throw Exception(__EXCEPTSRC__, "Error allocating Lua State");
    }
    
    luaL_openlibs(mLua);
}

Director::~Director() {
    lua_close(mLua);
}

void Director::addEntity(const std::string &name, const da::EntityRef &entity) {
    mEntities[name] = entity;
}

void Director::addEntity(const std::string &name, const da::EntityPtr &entity) {
    if (entity) {
        mEntities[name] = da::EntityRef(entity);
    }
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
    lua_register(mLua, name.c_str(), callback);
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
            if (mProgression = Any) {
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

Director::Exception::Exception(const std::string &where, unsigned long line,
                               const std::string &source,
                               const std::string &what) :
DAException(where, line, source, what) { }
