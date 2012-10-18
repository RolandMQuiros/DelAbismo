#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <map>
#include <queue>
#include <lua.hpp>

#include <da/Entity.h>
#include <da/DAException.h>

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
    
    Director();
    ~Director();
    
    /**
     * Add an Entity to be controlled by this Director
     */
    void addEntity(const std::string &name, const da::EntityRef &entity);
    void addEntity(const std::string &name, const da::EntityPtr &entity);
    
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
     */
    bool next();

    /**
     * Called by systems when a command is finished.  Typically called by a
     * delegate/event handler.
     *
     * Internally, it decrements a mapping keyed by the given entity reference,
     * indicating the number of commands currently acting on that entity.
     *
     * @param $entity
     *   Entity targeted by a scene command
     */
    void onFinish(const da::EntityRef &entity);
    void onFinish(const da::EntityPtr &entity);
    
    struct Exception : public da::DAException {
        Exception(const std::string &where, unsigned long line,
                  const std::string &source, const std::string &what);
    };

private:
    typedef std::map<da::EntityRef,
                     unsigned int,
                     std::owner_less<da::EntityRef> > EntityCommandMap;
    lua_State *mLua;
    std::queue<lua_State *> mLuaThreads;
    
    std::map<std::string, da::EntityRef> mEntities;
    EntityCommandMap mActiveTargets;
    
    Progression mProgression;
};

#endif
