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

typedef std::set<EntityRef, std::owner_less<EntityRef> > EntityGroup;

class EntityManager {
public:
    EntityManager();
    
    EntityPtr create();
    
    void refresh(const EntityPtr &entity);
    void refresh(const EntityRef &entity);
    
    void remove(const EntityPtr &entity);
    void remove(const EntityRef &entity);
    
    void clear();
    
    EntityRef get(unsigned int id) const;
    
    void addToGroup(const EntityRef &entity, const std::string &group);
    void addToGroup(const EntityPtr &entity, const std::string &group);
    
    void removeFromGroup(const EntityRef &entity,
                         const std::string &group);
    void removeFromGroup(const EntityPtr &entity,
                         const std::string &group);
    
    void removeGroup(const std::string &group);
    
    const EntityGroup &getGroup(const std::string &group) const;
    
    void addBehavior(const BehaviorPtr &behavior);
    void updateBehavior(const sf::Time &deltaTime, const BehaviorPtr &behavior);
    
    struct Exception : public DAException {
        Exception(const std::string &where, unsigned long line,
                  const std::string &source, const std::string &what);
    };
private:
    typedef std::unordered_map<std::string, EntityGroup,
                               std::hash<const std::string &> > GroupMap;
    typedef std::vector<EntityPtr>::iterator EntityIter;
    
    static const EntityGroup emptyGroup;
    static const char *updateBehaviorFuncName;
    
    unsigned int mvNextId;
    std::vector<EntityPtr> mvEntities;
    std::unordered_map<unsigned int, EntityIter> mvEntitySearch;
    GroupMap mvGroups;
    
    std::vector<BehaviorPtr> mvBehaviors;
};

}

#endif
