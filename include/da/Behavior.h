#ifndef DA_BEHAVIOR_H
#define DA_BEHAVIOR_H

#include <memory>
#include <unordered_set>
#include <queue>
#include <SFML/System/Time.hpp>

#include "da/Entity.h"

namespace da {

/**
 * Contains logic for entity behaviors.
 * A Behavior defines how an Entity composed of certain Attributes
 * acts.
 * 
 * For example, to represent a 2D box that moves from left to right at 100 units
 * per second, you can do something like the following:
 *
 * @code
 *   #include <da/Attribute.h>
 *   #include <da/Behavior.h>
 *       
 *   struct Transform : public Attribute<Transform> {
 *       float x;
 *       float y;
 *       Transform() : x(0.f), y(0.f) { }
 *   };
 *
 *   struct Box : public Attribute<Box> {
 *       float width;
 *       float height;
 *       Box() : width(1.f), height(1.f) { }
 *   };
 *       
 *   class BoxMover : public Behavior {
 *   public:
 *       bool isCompatible(const Entity &entity) const {
 *           return entity.hasComponent<Transform>();
 *       }
 *       
 *       void updateEntities(EntityGroup &entities) {
 *           for (EntityGroup::iterator iter = entities.begin();
 *                iter != entities.end();
 *                iter++) {
 *               Transform &xform = entities.getComponent<Transform>();
 *               Box &box = entities.getComponent<Box>();
 *               
 *               xform += 100.f * getDelta().asSeconds();
 *
 *               // Not a real function
 *               drawRect(xform.x, xform.y, box.width, box.height);
 *           }
 *       }
 *   };
 * @endcode
 *
 * To instantiate the box, do something like this in your initialization code:
 *
 * @code
 *   EntityManager manager;
 *   ...
 *   // Register our behavior to the entity manager.  Remember to do this before
 *   // adding any entities!
 *   BehaviorPtr<BoxMover> mover(new BoxMover());
 *   manager.addBehavior(mover);
 *
 *   // Create our box entity
 *   EntityPtr entity = manager.create();
 *   entity->addAttribute(new Transform());
 *   entity->addAttribute(new Box());
 *   // Refresh our entity
 *   manager.refresh(entity);
 *   ...
 * @endcode
 *
 * Finally, update the behavior
 *
 * @code
 *   mover->update(dt);
 * @endcode
 *
 * where dt is the delta time.
 *
 * @see Attribute
 * @see Entity
 * @see EntityManager
 */
class Behavior {
public:
    /**
     * Constructs a new Behavior
     */
    Behavior();
    
    /**
     * Virtual destructor
     */
    virtual ~Behavior();
    
    /**
     * Sets whether this Behavior is active.
     * Active Behaviors are updated every frame.  Inactive ones are not.
     * Simple as that.
     * @param $active
     *   whether or not this Behavior should be active
     */
    void setActive(bool active);
    
    /**
     * Returns whether or not this Behavior is active.
     * Active Behaviors are updated every frame.  Inactive ones are not.
     * @return
     *   true if this Behavior is active, false otherwise.
     */
    bool isActive() const;
    
    /**
     * Notifies this Behavior of a change in an Entity's composition.
     * If the given entity is compatible with this behavior, it will added to
     * this behavior's list of active entities.  If the entity exists in that
     * list, and is no longer compatible, it will be removed.
     * @param $entity
     *   reference to entity to refresh
     * @see isCompatible
     */
    void refreshEntity(const EntityRef &entity);

    /**
     * Called after this Behavior is added to an EntityManager.
     * Put any initialization code that shouldn't be handled by the constructor
     * here.
     * @see EntityManager
     */
    virtual void initialize();
    
    /**
     * Called after this Behavior is removed from an EntityManager.
     * Put any tear down code that shouldn't be handled by the destructor here.
     * @see EntityManager
     */
    virtual void dispose();
    
    /**
     * Updates this Behavior
     * @param $deltaTime
     *   time between update frames
     */
    void update(const sf::Time &deltaTime);
    
protected:
    /**
     * Returns the time since the last update
     * @return the time since the last update
     */
    const sf::Time &getDelta() const;
    
    /**
     * Adds an Entity to this Behavior's active list
     * @param $entity
     *   reference to entity added
     */
    void addEntity(const EntityRef &entity);
    
    /**
     * Removes an Entity from this Behavior's active list
     * @param $entity
     *   reference to entity removed
     */
    void removeEntity(const EntityRef &entity);
    
    /**
     * Returns true if an Entity meets this Behavior's requirements.
     * Override this function to analyze an Entity's composition.  That is,
     * if it has the right Attributes.
     * @param $entity
     *   entity to check
     * @return true if $entity is compatible, false otherwise
     */
    virtual bool isCompatible(const Entity &entity) const=0;
    
    /**
     * Called when an Entity is successfully added to the active list
     * @param $entity
     *   reference to entity added
     */
    virtual void addedEntity(const EntityRef &entity);
    
    /**
     * Called when an Entity is successfully removed from the active list
     * @param $entity
     *   reference to entity removed
     */
    virtual void removedEntity(const EntityRef &entity);
    
    /**
     * Updates this behavior.
     * Called by update() after adding and removing Entities from the active
     * list.  Must be overridden by all subclasses.
     * @param $entities
     *   set of entities to update
     */
    virtual void updateEntities(EntityGroup &entities)=0;
    
private:
    bool mIsActive;
    unsigned long mDependencies;
    sf::Time mDelta;
    
    EntityGroup mActive;
    std::queue<EntityRef> mAdded;
    std::queue<EntityRef> mRemoved;

};

/** Smart pointer to a Behavior.  Use this when ownership is shared. */
typedef std::shared_ptr<Behavior> BehaviorPtr;
/** Weak pointer to a Behavior.  Use this when the calling code does not
    have ownership */
typedef std::weak_ptr<Behavior> BehaviorRef;

}

#endif
