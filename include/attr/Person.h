#ifndef ATTR_PERSON_H
#define ATTR_PERSON_H

#include <SFML/System/Vector2.hpp>
#include <da/Attribute.h>
#include "CardinalDirection.h"

namespace attr {

struct Person : public da::Attribute<Person> {
    sf::Vector2f previousPosition;
};

}

#endif
