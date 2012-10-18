/**
 * A Spatial provides 2D rendering capabilities to da::Entities with the
 * appropriate da::Attributes.
 *
 * da::Entities that support Spatials generally, but not always, contain
 * attr::Transform and attr::Depth attributes, which allow the rendered content
 * to be moved about the screen and in a specified order, respectively.
 *
 * Internally, each derivation of Spatial keeps a unique type ID used by
 * bhvr::SpatialRenderer in order to create the appropriate Spatial for a
 * da::Entity.
 *
 * <B>To work with bhvr::SpatialRenderer properly, a derivation of Spatial must
 * contain the following method</B>
 * @code
 *   public:
 *       static SpatialBase *create(da::Entity &e);
 * @endcode
 * <B>and be registered with the Renderer via
 * bhvr::SpatialRenderer::registerSpatial<SpatialType>().</B>  This method can
 * return NULL, and should if a da::Entity doesn't meet certain da::Attribute
 * requirements.
 *
 * As a rule of thumb, use SpatialBase instead of Spatial for abstractions, such
 * as for collections and such.
 *
 * @see da::Entity
 * @see attr::Transform
 * @see attr::Depth
 * @see bhvr::SpatialRenderer
 */

#ifndef DA_SPATIAL_H
#define DA_SPATIAL_H

#include <unordered_map>
#include <functional>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>

#include "da/Entity.h"

namespace da {
    
typedef unsigned int SpatialId;

/**
 * Base class for all Spatials.  Maintains a reference to a Spatial's owning
 * da::Entity.
 */
class SpatialBase : public sf::Drawable {
private:
    /** Reference to owning da::Entity */
    da::Entity &mEntity;

public:
    /**
     * Constructs a new SpatialBase with the specified owning da::Entity
     *
     * @param $entity
     *   Reference to owning da::Entity
     */
    SpatialBase(da::Entity &entity) :
    mEntity(entity) { }
    
    /**
     * Returns reference to this SpatialBase's owning da::Entity
     * @return
     *   Reference to this' owning da::Entity
     */
    da::Entity &getEntity() {
        return mEntity;
    }
    
protected:
    /** Unique ID counter.  Each derivation of SpatialBase contains a unique
        value of this counter */
    static SpatialId sNextId;

};

template <class Derived>
class Spatial : public SpatialBase {
private:
    /** This Spatial type's unique ID number */
    static SpatialId msTypeId;

public:
    /**
     * Constructs a new Spatial with the specified owning da::Entity.
     * @param $entity
     *   Reference to owning da::Entity.
     */
    Spatial(da::Entity &entity) :
    SpatialBase(entity) {
        if (msTypeId == 0) {
            msTypeId = ++sNextId;
        }
    }
    
    /**
     * Destructor
     */
    virtual ~Spatial() { }
    
    /**
     * Returns the ID number of the Spatial's type.  For use in static
     * static contexts, or when you don't need an instance of the Spatial.
     * @return Spatial type ID number
     */
    static SpatialId typeId() {
        if (msTypeId == 0) {
            msTypeId = ++sNextId;
        }
        
        return msTypeId;
    }
    
    /**
     * Returns the ID number of this Spatial's type.  For use when you don't
     * have the specific derived type of a Spatial available.
     * @return this Spatial's type ID number
     */
    SpatialId getTypeId() const {
        return msTypeId;
    }
};

template <class Derived> SpatialId Spatial<Derived>::msTypeId = 0;

}

#endif
