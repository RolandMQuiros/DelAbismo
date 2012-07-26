#ifndef ATTR_TRANSFORM_H
#define ATTR_TRANSFORM_H

#include <SFML/Graphics/Transformable.hpp>
#include "da/Attribute.h"

namespace attr {

struct Transform : public da::Attribute,
                   public sf::Transformable {
    static const char *TypeName;
    Transform();
};

}

#endif
