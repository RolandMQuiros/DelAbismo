/**
 * Primary rendering behavior for entities with 2D graphics.
 *
 * An eligible Entity at least the following attributes:
 *   - attr::Transform
 *   - attr::Depth.
 *
 * When adding a Entity, bhvr::SpatialRenderer will check a table of
 * registered Spatial types to see if an associated one exists.
 *
 * bhvr::SpatialRenderer's is chiefly meant to sort 2D renders to simulate
 * depth, or distance from the player's view.
 *
 * @see Spatial
 * @see Entity
 * @see attr::Transform
 * @see attr::Depth
 */

#ifndef DA_BHVR_SPATIALRENDERER_H
#define DA_BHVR_SPATIALRENDERER_H

#include <functional>
#include <map>
#include <set>

#include <SFML/Graphics/RenderTarget.hpp>

#include "da/Behavior.h"
#include "da/twod/Spatial.h"

namespace da {
namespace bhvr {

/**
 * Type of a Spatial creation callback
 */
typedef std::function<SpatialBase *(Entity &e)> SpatialCreationFn;

/**
 * Compares two Spatials std::shared_ptr, based on attr::Depth
 * @param $a
 *   Pointer to first Spatial
 * @param $b
 *   Pointer to second Spatial
 * @return
 *   true if the Depth of b is greater than the Depth of a, false
 *   otherwise.
 *    
 * @see attr::Depth
 */
bool spatialLess(const std::shared_ptr<SpatialBase> &a,
                 const std::shared_ptr<SpatialBase> &b);

class SpatialRenderer : public Behavior {
protected:
    /**
     * Checks if a given Entity is compatible with this SpatialRenderer.
     * Returns true if $entity contains:
     *   - attr::Transform
     *   - attr::Depth
     * @param $entity
     *   Reference to entity to check
     * @return
     *   true, if $entity meets the requirements, false otherwise
     */
    bool isCompatible(const Entity &entity) const;
    
    /**
     * Called when a Entity is added to this Behavior.
     *
     * Overrides Behavior::addedEntity.
     * @param $entity
     *   Reference to Entity added
     * @see Behavior::addedEntity
     */
    void addedEntity(const EntityRef &entity);
    
    /**
     * Called when a Entity is removed from this Behavior.
     *
     * Overrides Behavior::addedEntity.
     * @param $entity
     *   Reference to Entity removed
     * @see Behavior::removedEntity
     */
    void removedEntity(const EntityRef &entity);
    
    
    void updateEntities(EntityGroup &entities);

private:
    typedef std::shared_ptr<SpatialBase> SpatialPtr;
    typedef std::map<unsigned int, SpatialCreationFn> SpatialCreationMap;
    
    sf::RenderTarget &mTarget;
    SpatialCreationMap mRegistered;
    std::vector<SpatialPtr> mSpatials;

public:
    SpatialRenderer(sf::RenderTarget &target);
    
    template <class Spatial> void registerSpatial() {
        SpatialCreationMap::iterator search =
            mRegistered.find(Spatial::typeId());
        
        if (search == mRegistered.end()) {
            mRegistered[Spatial::typeId()] = Spatial::create;
        }
    }

};

}
}

#endif
