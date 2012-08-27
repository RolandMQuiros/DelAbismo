#ifndef DA_ENTITY_H
#define DA_ENTITY_H

#include <memory>
#include <sstream>
#include <unordered_map>
#include <set>

#include "da/Attribute.h"
#include "da/DAException.h"

namespace da {

class Entity {
private:
    typedef std::unordered_map<unsigned int, AttributePtr> AttributeMap;
public:
    typedef AttributeMap::const_iterator Iterator;
    
    struct Exception : public DAException {
        Exception(const std::string &where, unsigned long line,
                  const std::string &source, const std::string &what);
    };
    
    Entity(unsigned int id);
    
    unsigned int getId() const;
    unsigned long getAttributeBits() const;
    
    void setActive(bool active);
    bool isActive() const;
    
    void addAttribute(const AttributePtr &attribute);
    void addAttribute(IAttribute *attribute);
    
    void removeAttribute(const AttributePtr &attribute);
    void removeAttribute(const AttributeRef &attribute);
    
    template <class T> void removeAttribute() {
        AttributeMap::iterator iter = mvAttributes.find(T::typeId());
        
        if (iter != mvAttributes.end()) {
            mvAttributes.erase(iter);
        }
    }
    
    template <class T> bool hasAttribute() const {
        Iterator iter = mvAttributes.find(T::typeId());
        bool ret = iter != mvAttributes.end() &&
                   iter->second;
        
        return ret;
    }
    
    // never throws
    template <class T> std::weak_ptr<T> getAttributeRef() const {
        Iterator iter = mvAttributes.find(T::typeId());
        std::weak_ptr<T> ret;
        
        if (iter != mvAttributes.end()) {
            ret = std::static_pointer_cast<T>(iter->second);
        }
        
        return ret;
    }
    
    // throws when search fails
    template <class T> T &getAttribute() const {
        Iterator iter = mvAttributes.find(T::typeId());
        
        if (iter != mvAttributes.end()) {
            return *std::static_pointer_cast<T>(iter->second);
        }
        
        std::stringstream err;
        
        err << "Entity (id = " << getId() << ") does not contain "
            << " attribute (" << T::typeId() << ")";
        
        throw Exception(__RELFILE__, __LINE__,
                        "Entity::getAttribute<T>() const", err.str());
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
typedef std::set<EntityRef, std::owner_less<EntityRef> > EntityGroup;

}

#endif
