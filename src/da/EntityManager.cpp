#include <stdexcept>
#include "da/EntityManager.h"

namespace da {

const EntityGroup EntityManager::emptyGroup;
const char *EntityManager::updateBehaviorFuncName = 
    "da::EntityManager::updateBehavior(const sf::Time &, "
                                      "const da::BehaviorPtr &)";

EntityManager::EntityManager() :
mvNextId(0) {
    
}
    
EntityPtr EntityManager::create() {
    EntityPtr ret(new Entity(++mvNextId));
    
    mvEntities.push_back(ret);
    mvEntitySearch[ret->getId()] = mvEntities.end() - 1;
    
    return ret;
}

void EntityManager::refresh(const EntityPtr &entity) {
    std::unordered_map<unsigned int, EntityIter>::iterator search =
        mvEntitySearch.find(entity->getId());
    
    // Can only refresh entities that exist in the EntityManager
    if (search == mvEntitySearch.end()) {
        return;
    }
    
    // Notify behaviors of changes
    for (unsigned int i = 0; i < mvBehaviors.size(); i++) {
        mvBehaviors[i]->refreshEntity(entity);
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
        mvEntitySearch.find(entity->getId());
    EntityRef ref(entity);
    
    // Check if entity exists from the EntityManager
    if (search != mvEntitySearch.end()) {
        
        // Remove entity from whatever groups it belonged to
        GroupMap::iterator groupIt;
        for (groupIt = mvGroups.begin(); groupIt != mvGroups.end(); groupIt++) {
            EntityGroup &group = groupIt->second;
            EntityGroup::iterator ent = group.find(ref);
            
            if (ent != group.end()) {
                group.erase(ent);
            }
        }
        
        // Erase entity from active and search lists
        mvEntities.erase(search->second);
        mvEntitySearch.erase(search);
    }
}

void EntityManager::remove(const EntityRef &entity) {
    remove(entity.lock());
}

EntityRef EntityManager::get(unsigned int id) const {
    std::unordered_map<unsigned int, EntityIter>::const_iterator search =
        mvEntitySearch.find(id);
    EntityRef ret;
    
    if (search != mvEntitySearch.end()) {
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
    if (mvEntitySearch.find(entity.lock()->getId()) == mvEntitySearch.end()) {
        return;
    }
    
    mvGroups[group].insert(entity);
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
    
    GroupMap::iterator groupIt = mvGroups.find(group);
    if (groupIt != mvGroups.end()) {
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
    GroupMap::iterator groupIt = mvGroups.find(group);
    if (groupIt != mvGroups.end()) {
        mvGroups.erase(groupIt);
    }
}

const EntityGroup &EntityManager::getGroup(const std::string &group) const {
    GroupMap::const_iterator groupIt = mvGroups.find(group);
    if (groupIt != mvGroups.end()) {
        return groupIt->second;
    }
    
    return emptyGroup;
}

void EntityManager::addBehavior(const BehaviorPtr &behavior) {
    if (behavior) {
        behavior->initialize();
        mvBehaviors.push_back(behavior);
    }
}

void EntityManager::updateBehavior(const sf::Time &deltaTime,
                                   const BehaviorPtr &behavior) {
    try {
        if (behavior) {
            behavior->update(deltaTime);
        }
    } catch (std::exception &e) {
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
