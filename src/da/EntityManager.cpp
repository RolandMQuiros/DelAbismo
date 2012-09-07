#include <stdexcept>
#include "da/EntityManager.h"

namespace da {

const EntityGroup EntityManager::emptyGroup;
const char *EntityManager::updateBehaviorFuncName = 
    "da::EntityManager::updateBehavior(const sf::Time &, "
                                      "const da::BehaviorPtr &)";

EntityManager::EntityManager() :
mNextId(0) {
    
}
    
EntityPtr EntityManager::create() {
    // Create a new entity with the next available ID number
    EntityPtr ret(new Entity(++mNextId));
    
    // Add entity to list
    mEntities.push_back(ret);
    // Add entity to search list
    mEntitySearch[ret->getId()] = mEntities.end() - 1;
    
    return ret;
}

void EntityManager::refresh(const EntityPtr &entity) {
    std::unordered_map<unsigned int, EntityIter>::iterator search =
        mEntitySearch.find(entity->getId());
    
    // Can only refresh entities that exist in the EntityManager
    if (search == mEntitySearch.end()) {
        return;
    }
    
    // Notify behaviors of changes
    for (unsigned int i = 0; i < mBehaviors.size(); i++) {
        mBehaviors[i]->refreshEntity(entity);
    }
}

void EntityManager::refresh(const EntityRef &entity) {
    if (!entity.expired()) {
        refresh(entity.lock());
    }
}

void EntityManager::remove(const EntityPtr &entity) {
    if (!entity) {
        return;
    }
    
    std::unordered_map<unsigned int, EntityIter>::iterator search =
        mEntitySearch.find(entity->getId());
    EntityRef ref(entity);
    
    // Check if entity exists from the EntityManager
    if (search != mEntitySearch.end()) {
        
        // Remove entity from whatever groups it belonged to
        GroupMap::iterator groupIt;
        for (groupIt = mGroups.begin(); groupIt != mGroups.end(); groupIt++) {
            EntityGroup &group = groupIt->second;
            EntityGroup::iterator ent = group.find(ref);
            
            if (ent != group.end()) {
                group.erase(ent);
            }
        }
        
        // Erase entity from active and search lists
        mEntities.erase(search->second);
        mEntitySearch.erase(search);
    }
}

void EntityManager::remove(const EntityRef &entity) {
    remove(entity.lock());
}

void EntityManager::clear() {
    mGroups.clear();
    mEntitySearch.clear();
    mEntities.clear();
}

EntityRef EntityManager::get(unsigned int id) const {
    std::unordered_map<unsigned int, EntityIter>::const_iterator search =
        mEntitySearch.find(id);
    EntityRef ret;
    
    if (search != mEntitySearch.end()) {
        ret = *(search->second);
    }
    
    return ret;
}

void EntityManager::addToGroup(const EntityRef &entity,
                             const std::string &group) {
    if (entity.expired()) {
        return;
    }
    
    // Only entities that exist in the EntityManager can be added to a group
    if (mEntitySearch.find(entity.lock()->getId()) == mEntitySearch.end()) {
        return;
    }
    
    mGroups[group].insert(entity);
}

void EntityManager::addToGroup(const EntityPtr &entity,
                             const std::string &group) {
    addToGroup(entity, group);
}

void EntityManager::removeFromGroup(const EntityRef &entity,
                                    const std::string &group) {
    if (entity.expired()) {
        return;
    }
    
    GroupMap::iterator groupIt = mGroups.find(group);
    if (groupIt != mGroups.end()) {
        EntityGroup::iterator entityIt = groupIt->second.find(entity);
        if (entityIt != groupIt->second.end()) {
            groupIt->second.erase(entityIt);
        }
    }
}

void EntityManager::removeFromGroup(const EntityPtr &entity,
                                    const std::string &group) {
    removeFromGroup(entity, group);
}

void EntityManager::removeGroup(const std::string &group) {
    GroupMap::iterator groupIt = mGroups.find(group);
    if (groupIt != mGroups.end()) {
        mGroups.erase(groupIt);
    }
}

const EntityGroup &EntityManager::getGroup(const std::string &group) const {
    GroupMap::const_iterator groupIt = mGroups.find(group);
    if (groupIt != mGroups.end()) {
        return groupIt->second;
    }
    
    return emptyGroup;
}

void EntityManager::addBehavior(const BehaviorPtr &behavior) {
    if (behavior) {
        behavior->initialize();
        mBehaviors.push_back(behavior);
    }
}

void EntityManager::updateBehavior(const sf::Time &deltaTime,
                                   const BehaviorPtr &behavior) {
    try {
        if (behavior) {
            behavior->update(deltaTime);
        }
    } catch (std::exception &e) {
        // __RELFILE__ is a custom macro that stores the relative path to the
        // current file
        DAException except(__RELFILE__, __LINE__, updateBehaviorFuncName,
                           std::string("Error updating behavior: ") + e.what());
        throw except;
    } catch (DAException &except) {
        DAException except(__RELFILE__, __LINE__, updateBehaviorFuncName,
                           "Error updating behavior");
        except.pushMessage(except);
        throw except;
    }
}

}
