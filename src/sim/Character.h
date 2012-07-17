#ifndef SIM_CHARACTER_H
#define SIM_CHARACTER_H

#include <SFML/Graphics/Vector2.hpp>
#include "da/Attribute.h"

namespace sim {

struct Character : public da::Attribute {
    sf::Vector2f previousPosition;
    
    
    Character();
};
    
}

#endif
