#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <map>
#include <queue>
#include <lua.hpp>

#include <da/Entity.h>
#include <da/DAException.h>

/**
 * Runs Lua scripts that describe cutscenes, or sequences controlled by the
 * game, itself.
 *
 *
 *
 * The director is a singleton, so only one instance of it should exist in the
 * game.  This merely gives us a nice way to give Lua C callbacks access to the
 * Director without resorting to an explicit global variable.
 *
 * Workflow:
 *   director.addEntity("entity#1", entity1);
 *   ...
 *
 *
 * In a callback:
 *   void sceneAction(luaState *L) {
 *       Director.addTarget(specified target names)
 *   }
 */
class Director {
public:
    enum Progression {
        /** Run the next block after any command in the current block
            finishes */
        Any,
        /** Run the next block once every command in the current block
            finishes */
        All
    };
    
    ~Director();
    static Director &getInstance();
    
    /**
     * Add an Entity to be controlled by this Director
     */
    void addEntity(const std::string &name, const da::EntityRef &entity);
    void addEntity(const std::string &name, const da::EntityPtr &entity);
    
    void addActor(const da::EntityRef &entity);
    void addActor(const da::EntityPtr &entity);
    
    /**
     * Retreives an Entity by name
     */
    da::EntityRef getEntity(const std::string &name) const;
    
    /**
     * Sets whether or not the next block of commands is executed when
     * <ol>
     * <li> false: All commands in the block is finished
     * <li> true: Any command in the block is finished
     * </ol>
     * By default, this is set to false.
     */
    void setProgression(Progression progress);
    
    Progression getProgression() const;
    
    /**
     * Call this when an entity is targeted for a scene command.  You typically
     * want to call this in callbacks registered with this Director.
     */
    void addTarget(const std::string &name);
    
    /**
     * Register a C function with this Director's lua state
     */
    void registerCallback(const std::string &name, int callback(lua_State *));

    /**
     * Queues a script to be read.
     * @throws bhvr::Director::Exception
     */
    void enqueue(const std::string &filename);
    
    /**
     * Starts the enqueued scripts
     * @return true if there is still script content to execute, false otherwise
     */
    bool next();

    /**
     * Called by systems when a command is finished.  Typically called by a
     * delegate/event handler.
     *
     * Internally, it decrements a counter mapped to the given entity reference,
     * the counter indicating the number of commands currently acting on that
     * entity.  Once the counter reaches zero, the entity is removed from the
     * active list, and once the active list is empty, we move on to the next
     * block of scene script.
     *
     * @param $entity
     *   Entity targeted by a scene command
     */
    void onFinish(const da::EntityRef &entity);
    void onFinish(const da::EntityPtr &entity);
    void onFinish(const da::Entity &entity); // Don't use this
    void onFinish(const std::string &name);
    
    struct Exception : public da::DAException {
        Exception(const std::string &where, unsigned long line,
                  const std::string &source, const std::string &what);
    };

private:
    static Director *msInstance;
    typedef std::map<da::EntityRef,
                     unsigned int,
                     std::owner_less<da::EntityRef> > EntityCommandMap;
    lua_State *mLua;
    std::queue<lua_State *> mLuaThreads;
    
    std::map<std::string, da::EntityRef> mEntities;
    EntityCommandMap mActiveTargets;
    
    Progression mProgression;
    
    Director();
};

#endif
