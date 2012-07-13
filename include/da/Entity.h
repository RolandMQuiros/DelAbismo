#ifndef DA_ENTITY_H
#define DA_ENTITY_H

#include <memory>
#include <unordered_map>

#include "da/Attribute.h"

namespace da {

class Entity {
private:
    typedef std::unordered_map<std::string, AttributePtr,
                               std::hash<const std::string &>> AttributeMap;
public:
    typedef AttributeMap::const_iterator Iterator;
    
    Entity(unsigned int id);
    
    unsigned int getId() const;
    unsigned long getAttributeBits() const;
    
    void setActive(bool active);
    bool isActive() const;
    
    void addAttribute(const AttributePtr &attribute);
    
    void removeAttribute(const AttributePtr &attribute);
    void removeAttribute(const AttributeRef &attribute);
    
    template <class T> std::weak_ptr<T> getAttribute() const {
        Iterator iter = mvAttributes.find(T::TypeName);
        std::weak_ptr<T> ret;
        
        if (iter != mvAttributes.end()) {
            ret = std::static_pointer_cast<T>(iter->second);
        }
        
        return ret;
    }
    
    Iterator getIterator() const;
    bool hasNext(const Iterator &iterator) const;
private:
    unsigned int mvId;
    unsigned long mvAttrBits;
    bool mvActive;
    
    AttributeMap mvAttributes;
};

typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity> EntityRef;

}

#endif
