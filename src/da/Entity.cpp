#include "da/Entity.h"

namespace da {

Entity::Exception::Exception(const std::string &where,
                             unsigned long line,
                             const std::string &source,
                             const std::string &what) :
DAException(where, line, source, what) {
    
}
    
Entity::Entity(unsigned int id) :
mId(id),
mActive(true) {

}

unsigned int Entity::getId() const {
    return mId;
}

void Entity::setActive(bool active) {
    mActive = active;
}

bool Entity::isActive() const {
    return mActive;
}

void Entity::addAttribute(const AttributePtr &attribute) {       
    if (attribute) {
        if (attribute->getTypeId() > mAttributes.size()) {
            mAttributes.resize(attribute->getTypeId());
        }
        
        mAttributes[attribute->getTypeId()-1] = attribute;
    }
}

void Entity::addAttribute(AttributeBase *attribute) {
    if (attribute != NULL) {
        addAttribute(AttributePtr(attribute));
    }
}

void Entity::removeAttribute(const AttributePtr &attribute) {
    unsigned int index = attribute->getTypeId();
    if (index <= mAttributes.size() && mAttributes[index]) {
        mAttributes[index] = AttributePtr();
    }
}

void Entity::removeAttribute(const AttributeRef &attribute) {
    if (!attribute.expired()) {
        removeAttribute(attribute.lock());
    }
}

unsigned int Entity::getAttributeCount() const {
    return mAttributes.size();
}

}
