#ifndef ATTR_COLLIDER_H
#define ATTR_COLLIDER_H

#include <functional>
#include <SFML/Graphics/Rect.hpp>
#include <da/Attribute.h>

namespace attr {

class Collider : public da::Attribute<Collider> {
public:
    enum Type {
        AABB, // Axis-aligned bounding boxes; check against bounding box
        SAT   // Separating-axis theorem; check against polygon data
    };
    
    sf::FloatRect boundingBox;
    //da::Polygon2d polygon;
};

}

#endif
