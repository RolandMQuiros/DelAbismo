#ifndef DA_ENTITY_H
#define DA_ENTITY_H

#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <set>

#include "da/Attribute.h"
#include "da/DAException.h"

namespace da {

/**
 * An object in the game world
 * At a glance, an entity represents a "thing" in a game.  The player,
 * powerups, bullets, and enemies are considered entities.  Internally, a
 * Entity is simply a collection of data, such as position or direction.
 * This data, in turn, is represented by Attributes.  Thus, an Entity
 * is simply a bag of Attributes.
 *
 * Entities can only have a single Attribute of a type.  Consider this when
 * designing your Attributes.
 * @see da::Attribute
 * @see da::EntityManager
 * @see da::Behavior
 */
class Entity {
public:    
    /**
     * Internal exception.
     */
    struct Exception : public DAException {
        Exception(const std::string &where, unsigned long line,
                  const std::string &source, const std::string &what);
    };
    
    /**
     * Constructs a new Entity with the given ID number
     * @param $id
     *   ID number
     */
    Entity(unsigned int id);
    
    /**
     * Returns this Entity's ID number
     * @return ID number
     */
    unsigned int getId() const;
    
    /**
     * Sets whether this Entity is active
     * An active entity is manipulated by a da::Behavior, whereas an inactive
     * one is not.
     * @param $active
     *   Whether or not this Entity should be active
     */
    void setActive(bool active);
    
    /**
     * Returns whether this Entity is active
     * @return true if active, false otherwise
     */
    bool isActive() const;
    
    /**
     * Adds an Attribute to this Entity
     * When an Attribute is added to an Entity, that entity loosely owns
     * that attribute.  That is, the entity owns the master instance of that
     * attribute.  Attributes won't be completely destroyed until all references
     * to them go out of scope, but the reference held in this should have
     * the most influence on when that happens.
     * @param $attribute
     *   Smart pointer to attribute added
     */
    void addAttribute(const AttributePtr &attribute);
    
    /**
     * Adds an Attribute to this Entity
     * When an Attribute is added to an Entity, that entity loosely owns
     * that attribute.  That is, the entity owns the master instance of that
     * attribute.  Attributes won't be completely destroyed until all references
     * to them go out of scope, but the reference held in this should have
     * the most influence on when that happens.
     * @param $attribute
     *   Raw pointer to attribute added
     */
    void addAttribute(AttributeBase *attribute);
    
    /**
     * Removes an Attribute from this
     * @param $attribute
     *   attribute to remove
     */
    void removeAttribute(const AttributePtr &attribute);
    
    /**
     * Removes an Attribute from this
     * @param $attribute
     *   attribute to remove
     */
    void removeAttribute(const AttributeRef &attribute);
    
    unsigned int getAttributeCount() const;
    
    /**
     * Removes an Attribute from this
     * @tparam $T
     *   type of Attribute to remove
     */
    template <class T> void removeAttribute() {
        if (T::typeId() <= mAttributes.size() && mAttributes[T::typeId()-1]) {
            mAttributes[T::typeId()-1] = AttributePtr();
        }
    }
    
    /**
     * Returns whether or not this Entity has an Attribute
     * @tparam $T
     *   type of Attribute to check
     * @return
     *   true if Attribute exists, false otherwise
     */
    template <class T> bool hasAttribute() const {
        bool ret = T::typeId() <= mAttributes.size() &&
                   mAttributes[T::typeId()-1];
        
        return ret;
    }
    
    /**
     * Retreives a weak pointer to an Attribute
     * @tparam
     *   type of Attribute to return
     * @return
     *   weak pointer to requested Attribute if it exists, expired weak pointer
     *   otherwise
     */
    template <class T> std::weak_ptr<T> getAttributeRef() const {
        std::weak_ptr<T> ret;
        
        if (hasAttribute<T>()) {
            ret = std::static_pointer_cast<T>(mAttributes[T::typeId()-1]);
        }
        
        return ret;
    }
    
    /**
     * Retrieves a reference to an Attribute
     * @tparam $T
     *   type of Attribute to return
     * @return
     *   reference to requested Attribute if it exists.  Throws otherwise.
     * @throws
     *   Entity::Exception
     */
    template <class T> T &getAttribute() const {
        if (hasAttribute<T>()) {
            if (mAttributes[T::typeId()-1]) {
                return *std::static_pointer_cast<T>(mAttributes[T::typeId()-1]);
            } else {
                std::stringstream err;
                err << "Entity (id = " << getId() << ") contains expired "
                    << "attribute (" << T::typeId() << ")";
            }
        }
        
        std::stringstream err;
        
        err << "Entity (id = " << getId() << ") does not contain "
            << "attribute (" << T::typeId() << ")";
        
        // __RELFILE__ is a custom macro that stores the relative path to the
        // current file
        throw Exception(__RELFILE__, __LINE__,
                        "Entity::getAttribute<T>() const", err.str());
    }
    
private:
    unsigned int mId;
    unsigned long mAttrBits;
    bool mActive;
    
    std::vector<AttributePtr> mAttributes;
};

/** Smart pointer to an Entity.  Use this when ownership is shared */
typedef std::shared_ptr<Entity> EntityPtr;
/** Weak pointer to an Entity.  Use this when the calling code does not have
    ownership */
typedef std::weak_ptr<Entity> EntityRef;
/** Set of Entities */
typedef std::set<EntityRef, std::owner_less<EntityRef> > EntityGroup;

}

#endif
