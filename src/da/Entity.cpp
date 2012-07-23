#include "da/Entity.h"

namespace da {

Entity::Exception::Exception(const std::string &where,
                             unsigned long line,
                             const std::string &source,
                             const std::string &what) :
DAException(where, line, source, what) {
    
}
    
Entity::Entity(unsigned int id) :
mvId(id),
mvActive(true) {

}

unsigned int Entity::getId() const {
    return mvId;
}

unsigned long Entity::getAttributeBits() const {
    return mvAttrBits;
}

void Entity::setActive(bool active) {
    mvActive = active;
}

bool Entity::isActive() const {
    return mvActive;
}

void Entity::addAttribute(const AttributePtr &attribute) {
    if (attribute) {        
        mvAttributes[attribute->getTypeName()] = attribute;
    }
}

void Entity::addAttribute(Attribute *attribute) {
    addAttribute(AttributePtr(attribute));
}

void Entity::removeAttribute(const AttributePtr &attribute) {
    AttributeMap::iterator iter = mvAttributes.find(attribute->getTypeName());
    
    if (iter != mvAttributes.end()) {
        mvAttributes.erase(iter);
    }
}

void Entity::removeAttribute(const AttributeRef &attribute) {
    if (!attribute.expired()) {
        removeAttribute(attribute.lock());
    }
}

bool Entity::hasNext(const Iterator &iterator) const {
    return iterator != mvAttributes.end();
}

}
