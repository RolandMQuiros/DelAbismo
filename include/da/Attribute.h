/**
 * Base class for all Attributes.
 * Uses "curiously recurring template pattern" to give each derived template a
 * unique ID number, as described
 * <a href="http://reddogstone.wordpress.com/2010/09/24/unique-class-id-in-c/">
 * here</a>.
 *
 * Notes for myself:
 * When extending Attribute, you provide a template argument.  This effectively
 * makes a brand new type, with a new instance of msTypeId.  Without the
 * templating, all derived types would share a single instance of msTypeId, and
 * every new type made would pull them all to ++sNextId.
 */

#ifndef DA_ATTRIBUTE_H
#define DA_ATTRIBUTE_H

#include <memory>

namespace da {

typedef unsigned int AttributeId;

class AttributeBase {
public:
    virtual AttributeId getTypeId() const=0;

protected:
    static AttributeId sNextId;
    
};

template <class Derived>
class Attribute : public AttributeBase {
private:
    static AttributeId msTypeId;

public:
    Attribute() {
        if (msTypeId == 0) {
            msTypeId = ++sNextId;
        }
    }
    
    virtual ~Attribute() {
        
    }
    
    static AttributeId typeId() {
        if (msTypeId == 0) {
            msTypeId = ++sNextId;
        }
        
        return msTypeId;
    }
    
    AttributeId getTypeId() const {
        return msTypeId;
    }

};

template <class Derived> AttributeId Attribute<Derived>::msTypeId = 0;

typedef std::shared_ptr<AttributeBase> AttributePtr;
typedef std::weak_ptr<AttributeBase> AttributeRef;

}

#endif
