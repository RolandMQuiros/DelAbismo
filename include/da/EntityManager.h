#ifndef DA_ENTITYMANAGER_H
#define DA_ENTITYMANAGER_H

#include <set>
#include <string>
#include <vector>
#include <unordered_map>

#include <SFML/System/Time.hpp>
#include "da/DAException.h"
#include "da/Entity.h"
#include "da/Behavior.h"

namespace da {

/**
 * Manages Entities and Behaviors
 * EntityManager does what it says on the tin: organizes Entities.  It also
 * synchronizes Behaviors with any changes in the Entities, so the Behaviors
 * know which Entities to manipulate.
 */
class EntityManager {
public:
    /**
     * Constructs a new EntityManager
     */
    EntityManager();
    
    /**
     * Creates a new Entity
     * @return
     *   pointer to new entity
     */
    EntityPtr create();
    
    /**
     * Refreshes an Entity
     * Entities that had Attributes added or removed must be refreshed before
     * the changes take effect.
     * @param $entity
     *   entity to refresh
     */
    void refresh(const EntityPtr &entity);

    /**
     * Refreshes an Entity
     * Entities that had Attributes added or removed must be refreshed before
     * the changes take effect.
     * @param $entity
     *   entity to refresh
     */
    void refresh(const EntityRef &entity);
    
    /**
     * Removes an entity
     * @param $entity
     *   entity to remove */
    void remove(const EntityPtr &entity);
    
    /**
     * Removes an entity
     * @param $entity
     *   entity to remove */
    void remove(const EntityRef &entity);
    
    /**
     * Removes all entities
     */
    void clear();
    
    /**
     * Retrieves an Entity by its ID number
     * @param $id
     *   ID number
     * @return
     *   weak pointer to Entity.  Pointer is expired if the entity is not found
     */
    EntityRef get(unsigned int id) const;
    
    /**
     * Adds an Entity to a group
     * Entities can belong to a group, identified by a string name.  The entity
     * must already exist in this EntityManager for this method to succeed.
     * @param $entity
     *   entity to add to group
     * @param $group
     *   name of group to add $entity
     */
    void addToGroup(const EntityRef &entity, const std::string &group);
    
    /**
     * Adds an Entity to a group
     * Entities can belong to a group, identified by a string name.  The entity
     * must already exist in this EntityManager for this method to succeed.
     * @param $entity
     *   entity to add to group
     * @param $group
     *   name of group to add $entity
     */
    void addToGroup(const EntityPtr &entity, const std::string &group);
    
    /**
     * Removes an Entity from a group
     * @param $entity
     *   entity to remove from group
     * @param $group
     *   name of group to add $entity
     */
    void removeFromGroup(const EntityRef &entity,
                         const std::string &group);
    /**
     * Removes an Entity from a group
     * @param $entity
     *   entity to remove from group
     * @param $group
     *   name of group to add $entity
     */
    void removeFromGroup(const EntityPtr &entity,
                         const std::string &group);
    
    /**
     * Removes all Entities from the specified group.
     * @param $group
     *   group to remove
     */
    void removeGroup(const std::string &group);
    
    /**
     * Returns a set of all Entities in a given group
     * @param $group
     *   name of group
     * @return
     *   constant reference to group.  Empty if the group does not exist.
     */
    const EntityGroup &getGroup(const std::string &group) const;
    
    /**
     * Registers a Behavior with this EntityManager
     * @param $behavior
     *   Pointer to behavior to add
     */
    void addBehavior(const BehaviorPtr &behavior);
    
    /**
     * Updates a Behavior registered with this EntityManager
     * @param $deltaTime
     *   time since last update
     * @param $behavior
     *   behavior to update
     */
    void updateBehavior(const sf::Time &deltaTime, const BehaviorPtr &behavior);
    
    /**
     * Internal exception class
     */
    struct Exception : public DAException {
        Exception(const std::string &where, unsigned long line,
                  const std::string &source, const std::string &what);
    };
private:
    typedef std::unordered_map<std::string, EntityGroup> GroupMap;
    typedef std::vector<EntityPtr>::iterator EntityIter;
    
    static const EntityGroup emptyGroup;
    static const char *updateBehaviorFuncName;
    
    unsigned int mNextId;
    std::vector<EntityPtr> mEntities;
    std::unordered_map<unsigned int, EntityIter> mEntitySearch;
    GroupMap mGroups;
    
    std::vector<BehaviorPtr> mBehaviors;
};

}

#endif
