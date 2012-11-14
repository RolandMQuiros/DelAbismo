#ifndef DA_ATTRIBUTE_H
#define DA_ATTRIBUTE_H

#include <memory>

namespace da {

typedef unsigned int AttributeId;

/**
 * Base type for all Attributes.
 * @see da::Attribute
 */
class AttributeBase {
public:
    /**
     * Returns this da::AttributeBase's type ID number.
     * @return this da::AttributeBase's type ID number.
     */
    virtual AttributeId getTypeId() const=0;

protected:
    /** Static ID counter.  Every class that derives da::AttributeBase is
        assigned an increment of this counter as its type ID number */
    static AttributeId sNextId;
    
};

/**
 * Base class for da::Entity data.
 * A da::Attribute holds the data for a da::Entity's specific behavior.
 * Ideally, a da::Attribute should only hold plain old data (POD) or simple
 * mutators and accessors.
 * @see da::Entity
 * @see da::Behavior
 */
template <class Derived>
class Attribute : public AttributeBase {
private:
    /** This da::Attribute's type ID number */
    static AttributeId msTypeId;

public:
    /**
     * Constructs a new da::Attribute.
     * A da::Attribute's type ID number is assigned when the first instance of a
     * type is created, or if a type's ID is queried from a static context.
     * @see typeId
     */
    Attribute() {
        if (msTypeId == 0) {
            msTypeId = ++sNextId;
        }
    }
    
    /**
     * Virtual destructor.
     */
    virtual ~Attribute() {
        
    }
    
    /**
     * Returns the da::Attribute's type ID
     * Use this when you have an da::Attribute's type, but not an instance of
     * that type.
     * @return type ID
     * @see getTypeId
     */
    static AttributeId typeId() {
        if (msTypeId == 0) {
            msTypeId = ++sNextId;
        }
        
        return msTypeId;
    }
    
    /**
     * Returns this da::Attribute's type ID
     * @return type ID
     */
    AttributeId getTypeId() const {
        return typeId();
    }

};

/** Smart pointer to an Attribute.  Use this when an Attribute has shared
    ownership */
typedef std::shared_ptr<AttributeBase> AttributePtr;
/** Weak pointer to an Attribute.  Use this when the calling code needs a
    reference, but does not have ownership of the Attribute */
typedef std::weak_ptr<AttributeBase> AttributeRef;

template <class Derived> AttributeId Attribute<Derived>::msTypeId = 0;

}

#endif
