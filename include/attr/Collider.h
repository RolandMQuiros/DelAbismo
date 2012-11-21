#ifndef ATTR_COLLIDER_H
#define ATTR_COLLIDER_H

#include <set>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <da/Attribute.h>
#include <da/Entity.h>

#include "Collision.h"

namespace attr {

struct Collider : public da::Attribute<Collider> {
    /** Collision method */
    enum Method {
        AABB, // Axis-aligned bounding boxes; check against bounding box
        SAT   // Separating-axis theorem; check against polygon data
    } method;
    
    /** Whether or not collision detection on this Entity is enabled */
    bool isEnabled;
    /** Solid entities are pushed out of other solid entities on collision */
    bool isSolid;
    /** Active entities check other entities, and are checked by others.
        Passive entities are only checked by others, and do no checking of their
        own */
    bool isActive;
    /** Whether or not the Collider's geometry has changed.  Used by the
        CollisionManager to decide if it needs to be reinserted into the
        quadtree*/
    bool isChanged;
    
    /** Bounding box width */
    float width;
    /** Bouning box height */
    float height;
    
    /** Bounding box */
    sf::FloatRect boundingBox;
    
    /** Polygon mask */
    //da::Polygon2d polygon;
    
    /** List of collision events */
    std::vector<Collision> collisions;
};

}

#endif
