#ifndef DA_TRANSFORM_H
#define DA_TRANSFORM_H

#include <SFML/Graphics/Transformable.hpp>
#include "da/Attribute.h"

namespace da {

class Transform : public da::Attribute,
                  public sf::Transformable {
public:
    static const char *TypeName;
    Transform();
};

}

#endif
