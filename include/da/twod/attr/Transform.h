#ifndef DA_TWOD_ATTR_TRANSFORM_H
#define DA_TWOD_ATTR_TRANSFORM_H

#include <SFML/Graphics/Transformable.hpp>
#include "da/Attribute.h"

namespace da {
namespace twod {
namespace attr {

struct Transform : public da::Attribute<Transform>,
                   public sf::Transformable {
};

}
}
}

#endif
